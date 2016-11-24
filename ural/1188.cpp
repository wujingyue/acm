/**
multiset: erase(k) will remove all the elements with key of k
if a board can support the tome, the tome must be completely on the board
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <cctype>
using namespace std;

const int max_n = 128, max_r = 1024;
const int oo = 0x7fffffff;

struct Board {
	int y, x1, x2, peg1, peg2;
};
bool operator<(const Board &a, const Board &b) {
	return a.y < b.y;
}

int bot[max_n][max_r], support[max_n][max_r];
pair<int, int> aside[max_n][max_r], sum_aside[max_n];
int R, C, W, H, n;
Board b[max_n];
pair<int, int> ans;
multiset<int> s;

void input() {
	scanf("%d %d %d %d", &C, &R, &W, &H);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d %d", &b[i].y, &b[i].x1, &b[i].x2, &b[i].peg1, &b[i].peg2);
		b[i].x2 += b[i].x1;
		b[i].peg1 += b[i].x1;
		b[i].peg2 += b[i].x1;
	}
}

void solve() {
	sort(b, b + n);
	for (int i = 0; i < n; i++) {
		if (b[i].x2 - b[i].x1 < W || b[i].y + H > R)
			continue;
		for (int x = 0; x + b[i].x2 - b[i].x1 <= C; ++x) {
			int x1 = x, x2 = x + b[i].x2 - b[i].x1;
			if (x1 <= b[i].peg1 && b[i].peg1 <= x2 && x1 <= b[i].peg2 && b[i].peg2 <= x2 &&
					b[i].peg1 * 2 <= x1 + x2 && x1 + x2 <= b[i].peg2 * 2) {
				bot[i][x] = 0;
				continue;
			}
			if ((x1 <= b[i].peg1 && b[i].peg1 <= x2) ||
					(x1 <= b[i].peg2 && b[i].peg2 <= x2))
				bot[i][x] = 1;
			else
				bot[i][x] = 2;

		}
		s.clear();
		for (int x = 0; x + W <= C; ++x) {
			if (x + b[i].x2 - b[i].x1 <= C)
				s.insert(bot[i][x]);
			if (x + W - (b[i].x2 - b[i].x1) - 1 >= 0) {
				multiset<int>::iterator it = s.find(bot[i][x + W - (b[i].x2 - b[i].x1) - 1]);
				assert(it != s.end());
				s.erase(it);
			}
			assert(!s.empty());
			support[i][x] = *s.begin();
			assert(support[i][x] >= 0 && support[i][x] <= 2);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int x = 0; x + W <= C; ++x) {
			int x1 = x, x2 = x + W;
			if (b[i].x2 <= x1 || x2 <= b[i].x1) {
				aside[i][x] = make_pair(0, 0);
				continue;
			}
			if (x1 < b[i].peg1 && b[i].peg1 < x2 && x1 < b[i].peg2 && b[i].peg2 < x2) {
				aside[i][x] = make_pair(2, b[i].x2 - b[i].x1);
				continue;
			}
			if (b[i].peg1 <= x1 && b[i].peg2 <= x1) {
				int max_l;
				if (b[i].peg1 * 2 <= x1 && x1 <= b[i].peg2 * 2)
					max_l = x1;
				else if (b[i].peg1 * 2 >= x1)
					max_l = 2 * (x1 - b[i].peg1);
				else {
					assert(b[i].peg2 * 2 <= x1);
					max_l = 2 * b[i].peg2;
				}
				if (max_l < b[i].x2 - b[i].x1)
					aside[i][x] = make_pair(0, b[i].x2 - b[i].x1 - max_l);
				else
					aside[i][x] = make_pair(0, 0);
				continue;
			}
			if (b[i].peg1 >= x2 && b[i].peg2 >= x2) {
				int max_l;
				if (b[i].peg1 * 2 <= x2 + C && x2 + C <= b[i].peg2 * 2) {
					max_l = C - x2;
				} else if (b[i].peg1 * 2 >= x2 + C)
					max_l = 2 * (C - b[i].peg1);
				else {
					assert(b[i].peg2 * 2 <= x2 + C);
					max_l = 2 * (b[i].peg2 - x2);
				}
				if (max_l < b[i].x2 - b[i].x1)
					aside[i][x] = make_pair(0, b[i].x2 - b[i].x1 - max_l);
				else
					aside[i][x] = make_pair(0, 0);
				continue;
			}
			if (b[i].peg1 <= x1 && b[i].peg2 >= x2) {
				int max_l = max(x1, C - x2);
				if (max_l < b[i].x2 - b[i].x1)
					aside[i][x] = make_pair(max_l == 0 ? 2 : 1, b[i].x2 - b[i].x1 - max_l);
				else
					aside[i][x] = make_pair(1, 0);
				continue;
			}
			if (x1 < b[i].peg1 && b[i].peg1 < x2) {
				int max_l = C - x2;
				if (max_l < b[i].x2 - b[i].x1)
					aside[i][x] = make_pair(max_l == 0 ? 2 : 1, b[i].x2 - b[i].x1 - max_l);
				else
					aside[i][x] = make_pair(1, 0);
			} else {
				assert(x1 < b[i].peg2 && b[i].peg2 < x2);
				int max_l = x1;
				if (max_l < b[i].x2 - b[i].x1)
					aside[i][x] = make_pair(max_l == 0 ? 2 : 1, b[i].x2 - b[i].x1 - max_l);
				else
					aside[i][x] = make_pair(1, 0);
			}
		}
	}
	ans = make_pair(oo, oo);
	for (int x = 0; x + W <= C; x++) {
		sum_aside[0] = aside[0][x];
		for (int i = 1; i < n; i++) {
			// fprintf(stderr, "aside[%d][%d] = %d, %d\n", i, x, aside[i][x].first, aside[i][x].second);
			sum_aside[i].first = sum_aside[i - 1].first + aside[i][x].first;
			sum_aside[i].second = sum_aside[i - 1].second + aside[i][x].second;
		}
		int j = 0;
		for (int i = 0; i < n; i++) {
			while (j < n && b[j].y < b[i].y + H)
				j++;
			if (b[i].x2 - b[i].x1 >= W && b[i].y + H <= R) {
				pair<int, int> tmp = make_pair(
						sum_aside[j - 1].first - sum_aside[i].first,
						sum_aside[j - 1].second - sum_aside[i].second);
				assert(support[i][x] >= 0 && support[i][x] <= 2);
				tmp.first += support[i][x];
				if (tmp < ans) {
					/*
					cerr << tmp.first << ' ' << tmp.second << endl;
					cerr << "x = " << x << endl;
					cerr << "support = " << support[i][x] << "; " << "bot = " << bot[i][x] << endl;
					for (int k = i; k < j; k++)
						cerr << b[k].y << ' ' << b[k].x1 << ' ' << b[k].x2 << ' ' << b[k].peg1 << ' ' << b[k].peg2 << endl;
					*/
					ans = tmp;
				}
			}
		}
	}
}

void output() {
	printf("%d %d\n", ans.first, ans.second);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


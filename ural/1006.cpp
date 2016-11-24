/**
  typo * vs .
  | and - are not borders
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <complex>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <cctype>
using namespace std;

const char LU = (char)218, RU = (char)191, LB = (char)192, RB = (char)217, H = (char)196, V = (char)179;

struct Square {
	int x, y, k;
};

const int MAX_M = 64, MAX_N = 64;

vector<Square> s, ans;
int m, n;
char a[MAX_M][MAX_N];
bool used[MAX_M * MAX_M * MAX_M];

void input() {
	m = 20; n = 50;
	for (int x = 0; x < m; x++) {
		for (int y = 0; y < n; y++) {
			do {
				scanf("%c", &a[x][y]);
			} while (a[x][y] != LU &&
					a[x][y] != RU &&
					a[x][y] != LB &&
					a[x][y] != RB &&
					a[x][y] != V &&
					a[x][y] != H &&
					a[x][y] != '.');
		}
	}
}

bool valid(int x1, int y1, int x2, int y2) {
	if (!(a[x1][y1] == LU || a[x1][y1] == '*'))
		return false;
	if (!(a[x1][y2] == RU || a[x1][y2] == '*'))
		return false;
	if (!(a[x2][y1] == LB || a[x2][y1] == '*'))
		return false;
	if (!(a[x2][y2] == RB || a[x2][y2] == '*'))
		return false;
	for (int x = x1 + 1; x <= x2 - 1; x++) {
		if (!(a[x][y1] == V || a[x][y1] == '*'))
			return false;
		if (!(a[x][y2] == V || a[x][y2] == '*'))
			return false;
	}
	for (int y = y1 + 1; y <= y2 - 1; y++) {
		if (!(a[x1][y] == H || a[x1][y] == '*'))
			return false;
		if (!(a[x2][y] == H || a[x2][y] == '*'))
			return false;
	}
	return true;
}

void clear(int x, int y, int &n_lines) {
	if (a[x][y] != '*') {
		n_lines--;
		a[x][y] = '*';
	}
}

void solve() {
	s.clear();
	for (int x1 = 0; x1 < m; x1++) {
		for (int y1 = 0; y1 < n; y1++) {
			for (int k = 2; x1 + k - 1 < m && y1 + k - 1 < n; k++) {
				int x2 = x1 + k - 1, y2 = y1 + k - 1;
				bool poss = true;
				for (int x = x1; x <= x2; x++) {
					if (a[x][y1] == '.' || a[x][y2] == '.') {
						poss = false;
						break;
					}
				}
				if (poss) {
					for (int y = y1; y <= y2; y++) {
						if (a[x1][y] == '.' || a[x2][y] == '.') {
							poss = false;
							break;
						}
					}
				}
				if (poss) {
					bool useful = false;
					if (a[x1][y1] == LU)
						useful = true;
					if (a[x1][y2] == RU)
						useful = true;
					if (a[x2][y1] == LB)
						useful = true;
					if (a[x2][y2] == RB)
						useful = true;
					for (int x = x1 + 1; x < x2; x++) {
						if (a[x][y1] == V || a[x][y2] == V)
							useful = true;
					}
					for (int y = y1 + 1; y < y2; y++) {
						if (a[x1][y] == H || a[x2][y] == H)
							useful = true;
					}
					if (useful) {
						Square ss; ss.x = x1; ss.y = y1; ss.k = k;
						s.push_back(ss);
					}
				}
			}
		}
	}
	// fprintf(stderr, "s.size() = %u\n", s.size());
	memset(used, 0, sizeof used);
	int n_lines = 0;
	for (int x = 0; x < m; x++) {
		for (int y = 0; y < n; y++) {
			if (a[x][y] != '.')
				n_lines++;
		}
	}
	ans.clear();
	while (n_lines > 0) {
		int old_n_lines = n_lines;
		for (int i = 0; i < (int)s.size(); i++) {
			if (used[i])
				continue;
			int x1, y1, x2, y2;
			x1 = s[i].x; y1 = s[i].y; x2 = x1 + s[i].k - 1; y2 = y1 + s[i].k - 1;
			if (valid(x1, y1, x2, y2)) {
				bool useful = false;
				for (int x = x1; x <= x2; x++) {
					if (a[x][y1] != '*' || a[x][y2] != '*') {
						useful = true;
						break;
					}
				}
				if (!useful) {
					for (int y = y1; y <= y2; y++) {
						if (a[x1][y] != '*' || a[x2][y] != '*') {
							useful = true;
							break;
						}
					}
				}
				if (useful) {
					for (int x = x1; x <= x2; x++) {
						clear(x, y1, n_lines);
						clear(x, y2, n_lines);
					}
					for (int y = y1; y <= y2; y++) {
						clear(x1, y, n_lines);
						clear(x2, y, n_lines);
					}
					ans.push_back(s[i]);
					used[i] = true;
				}
			}
		}
		assert(n_lines < old_n_lines);
	}
}

void output() {
	printf("%u\n", ans.size());
	for (int i = (int)ans.size() - 1; i >= 0; i--)
		printf("%d %d %d\n", ans[i].y, ans[i].x, ans[i].k);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


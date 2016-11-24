/**
  p == 0, boundary check
  two words are the same
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

const int max_p = 16, max_n = 64, max_m = 64, max_l = 16;
const int max_len = 100;
const int module = 10000;

struct BigInt {
	int len;
	int digit[max_len];
};
void clear(BigInt &a) {
	memset(a.digit, 0, sizeof a.digit);
	a.len = 1;
}
void add(BigInt &a, const BigInt &b) {
	if (b.len > a.len)
		a.len = b.len;
	for (int i = 0; i < a.len; i++)
		a.digit[i] += b.digit[i];
	for (int i = 0; i < a.len; i++) {
		if (a.digit[i] >= module) {
			a.digit[i] -= module;
			a.digit[i + 1]++;
		}
	}
	if (a.digit[a.len] > 0)
		a.len++;
}

pair<int, int> transfer[max_p][max_l][max_n];
basic_string<int> forbid[max_p];
int n, m, p;
bool del[max_p];
BigInt c[max_m][max_p][max_l];
BigInt ans;

bool by_length(const basic_string<int> &a, const basic_string<int> &b) {
	return a.length() < b.length();
}

void input() {
	cin >> n >> m >> p;
	string alpha;
	cin >> alpha;
	for (int i = 0; i < p; i++) {
		string line;
		cin >> line;
		forbid[i].clear();
		for (size_t j = 0; j < line.size(); j++) {
			size_t pos = alpha.find(line[j]);
			assert(pos != string::npos);
			forbid[i].push_back(pos);
		}
	}
	sort(forbid, forbid + p, by_length);
	memset(del, 0, sizeof del);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < i; j++) {
			if (forbid[i].find(forbid[j]) != string::npos) {
				del[i] = true;
				break;
			}
		}
	}
	vector<basic_string<int> > forbid1;
	for (int i = 0; i < p; i++) {
		if (del[i])
			continue;
		forbid1.push_back(forbid[i]);
	}
	p = (int)forbid1.size();
	for (int i = 0; i < p; i++)
		forbid[i] = forbid1[i];
}

void solve() {
	if (p == 0)
		return;
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < (int)forbid[i].length(); j++) {
			for (int k = 0; k < n; k++) {
				basic_string<int> a = forbid[i].substr(0, j);
				a.push_back(k);
				bool found = false;
				for (int j1 = 0; j1 < (int)a.length(); j1++) {
					basic_string<int> sub = a.substr(j1);
					for (int i1 = 0; i1 < p; i1++) {
						if (forbid[i1].find(sub) == 0) {
							transfer[i][j][k] = make_pair(i1, sub.length());
							if (sub.length() == forbid[i1].length())
								transfer[i][j][k].first = -1;
							found = true;
							break;
						}
					}
					if (found)
						break;
				}
				if (!found)
					transfer[i][j][k] = make_pair(0, 0);
				// fprintf(stderr, "%d %d %d -> %d %d\n", i, j, k, transfer[i][j][k].first, transfer[i][j][k].second);
			}
		}
	}
	for (int k = 0; k < m; k++) {
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < (int)forbid[i].length(); j++)
				clear(c[k][i][j]);
		}
	}
	c[0][0][0].digit[0] = 1;
	for (int k = 0; k < m; k++) {
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < (int)forbid[i].length(); j++) {
				if (c[k][i][j].len == 1 && c[k][i][j].digit[0] == 0)
					continue;
				for (int ch = 0; ch < n; ch++) {
					int i1 = transfer[i][j][ch].first, j1 = transfer[i][j][ch].second;
					if (i1 == -1)
						continue;
					add(c[k + 1][i1][j1], c[k][i][j]);
				}
			}
		}
	}
}

void output() {
	clear(ans);
	if (p == 0) {
		ans.digit[0] = 1;
		for (int k = 0; k < m; k++) {
			BigInt ans1;
			clear(ans1);
			for (int i = 0; i < n; i++) {
				add(ans1, ans);
			}
			ans = ans1;
		}
	} else {
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < (int)forbid[i].length(); j++) {
				add(ans, c[m][i][j]);
			}
		}
	}
	printf("%d", ans.digit[ans.len - 1]);
	for (int i = ans.len - 2; i >= 0; i--) {
		printf("%04d", ans.digit[i]);
	}
	printf("\n");
}

int main() {
	input();
	solve();
	output();
	return 0;
}


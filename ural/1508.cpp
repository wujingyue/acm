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

const int max_n = 512, max_k = max_n;

int len[max_k], num_dot[max_n], num_cross[max_n];
bool c[max_n][max_k], d[max_n][max_k];
bool poss_cross[max_n], poss_dot[max_n];
char a[max_n];
int n, k;

void input() {
	cin >> n >> k;
	for (int i = 0; i < k; i++)
		cin >> len[i];
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

void solve() {
	num_dot[n] = num_cross[n] = 0;
	for (int i = n - 1; i >= 0; i--) {
		num_dot[i] = num_dot[i + 1];
		num_cross[i] = num_cross[i + 1];
		if (a[i] == '.')
			num_dot[i]++;
		if (a[i] == 'X')
			num_cross[i]++;
	}
	memset(c, 0, sizeof c);
	for (int i = 0; i < n; i++) {
		if (i + len[0] - 1 >= n)
			continue;
		if (num_dot[i] - num_dot[i + len[0]] > 0)
			continue;
		if (num_cross[0] - num_cross[i] > 0)
			continue;
		c[i][0] = true;
	}
	for (int j = 1; j < k; j++) {
		for (int i = 0; i < n; i++) {
			if (i + len[j] - 1 >= n)
				continue;
			if (num_dot[i] - num_dot[i + len[j]] > 0)
				continue;
			for (int i1 = 0; i1 < i; i1++) {
				if (!c[i1][j - 1])
					continue;
				if (i1 + len[j - 1] - 1 >= i - 1)
					continue;
				if (num_cross[i1 + len[j - 1]] - num_cross[i] > 0)
					continue;
				c[i][j] = true;
				break;
			}
		}
	}
#if 0
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (c[i][j])
				fprintf(stderr, "c: %d %d\n", i, j);
		}
	}
#endif
	memset(d, 0, sizeof d);
	for (int i = 0; i < n; i++) {
		if (i + len[k - 1] - 1 >= n)
			continue;
		if (num_dot[i] - num_dot[i + len[k - 1]] > 0)
			continue;
		if (num_cross[i + len[k - 1]] > 0)
			continue;
		d[i][k - 1] = true;
	}
	for (int j = k - 2; j >= 0; j--) {
		for (int i = 0; i < n; i++) {
			if (i + len[j] - 1 >= n)
				continue;
			if (num_dot[i] - num_dot[i + len[j]] > 0)
				continue;
			for (int i1 = i + 1; i1 < n; i1++) {
				if (!d[i1][j + 1])
					continue;
				if (i + len[j] - 1 >= i1 - 1)
					continue;
				if (num_cross[i + len[j]] - num_cross[i1] > 0)
					continue;
				d[i][j] = true;
				break;
			}
		}
	}
#if 0
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (d[i][j])
				fprintf(stderr, "d: %d %d\n", i, j);
		}
	}
#endif
}

bool possible_cross(int i) {
	if (a[i] == '.')
		return false;
	for (int i1 = 0; i1 < n; i1++) {
		for (int j = 0; j < k; j++) {
			if (i1 + len[j] - 1 >= i && i1 <= i && c[i1][j] && d[i1][j])
				return true;
		}
	}
	return false;
}

bool possible_dot(int i) {
	if (a[i] == 'X')
		return false;
	for (int j = -1; j < k; j++) {
		bool poss_left, poss_right;
		if (j == -1)
			poss_left = (num_cross[0] - num_cross[i] == 0);
		else {
			poss_left = false;
			for (int i1 = 0; i1 < n; i1++) {
				if (i1 + len[j] - 1 < i && c[i1][j] && num_cross[i1 + len[j]] - num_cross[i] == 0) {
					poss_left = true;
					break;
				}
			}
		}
		if (j == k - 1)
			poss_right = (num_cross[i + 1] == 0);
		else {
			poss_right = false;
			for (int i2 = 0; i2 < n; i2++) {
				if (i < i2 && d[i2][j + 1] && num_cross[i + 1] - num_cross[i2] == 0) {
					poss_right = true;
					break;
				}
			}
		}
		if (poss_left && poss_right)
			return true;
	}
	return false;
}

void output() {
	for (int i = 0; i < n; i++) {
		poss_cross[i] = possible_cross(i);
		poss_dot[i] = possible_dot(i);
		// fprintf(stderr, "%d: X%d .%d\n", i, poss_cross[i], poss_dot[i]);
	}
	for (int i = 0; i < n; i++) {
		if (!poss_cross[i] && !poss_dot[i]) {
			printf("Impossible\n");
			return;
		}
	}
	for (int i = 0; i < n; i++) {
		if (poss_cross[i] && poss_dot[i])
			printf("?");
		else if (poss_cross[i])
			printf("X");
		else
			printf(".");
	}
	printf("\n");
}

int main() {
	input();
	solve();
	output();
	return 0;
}


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

const int max_n = 32768;
const int max_m = 71;
const int max_h = 61;
const long long oo = 0x7fffffffffffffffLL;

long long c[max_m][max_h][max_n];
int n, m, h, idx;

/* i = m, j = h, k = n */
long long work(int i, int j, int k) {
	if (i <= 0)
		return 0;
	if (i > k)
		return 0;
	if (c[i][j][k] >= 0)
		return c[i][j][k];
	if (j == 1) {
		c[i][j][k] = 1;
	} else {
		assert(oo - work(i - 1, j - 1, k - i) >= work(i + 1, j - 1, k - i));
		c[i][j][k] = work(i - 1, j - 1, k - i) + work(i + 1, j - 1, k - i);
	}
	return c[i][j][k];
}

void init() {
	scanf("%d %d %d", &n, &h, &m);
	memset(c, -1, sizeof c);
	printf("%lld\n", work(m, h, n));
	int filled = 0;
	for (int i = 0; i < max_m; ++i) {
		for (int j = 0; j < max_h; ++j) {
			for (int k = 0; k < max_n; ++k) {
				if (c[i][j][k] >= 0)
					filled++;
			}
		}
	}
	cerr << "filled = " << filled << endl;
}

bool input() {
	scanf("%d", &idx);
	return idx != -1;
}

void print(int i, int j, int k, long long idx) {
	assert(idx >= 1 && idx <= work(i, j, k));
	if (j == 1) {
		printf("%d\n", i);
		return;
	}
	printf("%d ", i);
	long long left = work(i - 1, j - 1, k - i);
	if (idx <= left)
		print(i - 1, j - 1, k - i, idx);
	else
		print(i + 1, j - 1, k - i, idx - left);
}

void solve() {
	print(m, h, n, idx);
}

void output() {
}

int main() {
	init();
	while (input()) {
		solve();
		output();
	}
	return 0;
}


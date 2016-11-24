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

const int max_r = 32, max_c = 32, max_n = max_r * max_c / 4;
const int oo = 0x7fffffff;

int r, c;
char b[max_r][max_c];
int a[max_n][max_n];
int m, n;
int num[100];
char chs[max_n];
int lx[max_n], ly[max_n], slack[max_n], match[max_n];
bool vx[max_n], vy[max_n];

void input() {
	cin >> r >> c;
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			cin >> b[x][y];
		}
	}
	assert(r % 2 == 0 && c % 2 == 0);
}

bool search(int x) {
	vx[x] = true;
	for (int y = 0; y < n; y++) {
		if (!vy[y]) {
			int delta = lx[x] + ly[y] - a[x][y];
			if (delta == 0) {
				vy[y] = true;
				if (match[y] == -1 || search(match[y])) {
					match[y] = x;
					return true;
				}
			} else if (delta < slack[y])
				slack[y] = delta;
		}
	}
	return false;
}

void solve() {
	memset(num, 0, sizeof num);
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++)
			num[b[x][y] - 'a']++;
	}
	n = 0;
	for (int j = 0; j < 26; j++) {
		assert(num[j] % 4 == 0);
		for (int k = 0; k < num[j] / 4; k++) {
			chs[n] = 'a' + j;
			n++;
		}
	}
	m = 0;
	for (int x = 0; x < r / 2; x++) {
		for (int y = 0; y < c / 2; y++) {
			for (int j = 0; j < n; j++) {
				a[m][j] = 0;
				if (b[x][y] != chs[j])
					a[m][j]++;
				if (b[r - 1 - x][y] != chs[j])
					a[m][j]++;
				if (b[x][c - 1 - y] != chs[j])
					a[m][j]++;
				if (b[r - 1 - x][c - 1 - y] != chs[j])
					a[m][j]++;
			}
			m++;
		}
	}
	assert(m == n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			a[i][j] = -a[i][j];
	}
	memset(ly, 0, sizeof ly);
	for (int x = 0; x < n; x++) {
		lx[x] = -oo;
		for (int y = 0; y < n; y++)
			lx[x] = max(lx[x], a[x][y]);
	}
	memset(match, -1, sizeof match);
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++)
			slack[y] = oo;
		while (true) {
			memset(vx, 0, sizeof vx); memset(vy, 0, sizeof vy);
			if (search(x))
				break;
			int delta = oo;
			for (int y = 0; y < n; y++) {
				if (!vy[y] && slack[y] < delta)
					delta = slack[y];
			}
			for (int x = 0; x < n; x++) {
				if (vx[x])
					lx[x] -= delta;
			}
			for (int y = 0; y < n; y++) {
				if (vy[y])
					ly[y] += delta;
				else
					slack[y] -= delta;
			}
		}
	}
}

void output() {
	int ans = 0;
	for (int x = 0; x < n; x++) {
		ans -= lx[x];
		ans -= ly[x];
	}
	printf("%d\n", ans);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


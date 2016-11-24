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

const int MAX_N = 65536;
const int MAX_M = 128;
const int oo = 0x7fffffff;

string a;
string w[MAX_N];
int n, m;
int c[MAX_M], f[MAX_N];

const char mapping[] = {'2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5', '6', '6',
	'0', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};

bool input() {
	cin >> a;
	if (a == "-1")
		return false;
	m = a.size();
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	return true;
}

void solve() {
	for (int i = 0; i < m; i++) {
		c[i] = oo;
		for (int k = 0; k < n; k++) {
			if ((int)w[k].length() <= i + 1) {
				bool match = true;
				int j1 = i - (int)w[k].length() + 1;
				for (size_t j = 0; j < w[k].length(); j++) {
					if (mapping[w[k][j] - 'a'] != a[j1]) {
						match = false;
						break;
					}
					j1++;
				}
				if (match) {
					int j = i - (int)w[k].length();
					if (j >= 0) {
						if (c[j] < oo && c[j] + 1 < c[i]) {
							c[i] = c[j] + 1;
							f[i] = k;
						}
					} else {
						if (1 < c[i]) {
							c[i] = 1;
							f[i] = k;
						}
					}
				}
			}
		}
	}
}

void print(int i) {
	assert(c[i] < oo);
	if (i < (int)w[f[i]].length()) {
		printf("%s", w[f[i]].c_str());
		return;
	}
	print(i - w[f[i]].length());
	printf(" %s", w[f[i]].c_str());
}

void output() {
	if (c[m - 1] == oo)
		printf("No solution.\n");
	else {
		print(m - 1);
		printf("\n");
	}
}

int main() {
	while (input()) {
		solve();
		output();
	}
	return 0;
}


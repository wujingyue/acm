/**
 * no SCC is with size of 2
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
// #include <ext/hash_set>
using namespace std;
// using namespace __gnu_cxx;

const int max_n = 128;
const int max_m = max_n * max_n;

bool c[max_n][max_m];
int n, k;
vector<int> ans;

void init() {
	memset(c, 0, sizeof c);
	c[0][0] = true;
	for (int i = 0; i < max_n; i++) {
		// cerr << i << ' ' << c[i].size() << endl;
		for (int j = 0; j <= i * i; j++) {
			if (c[i][j]) {
				for (int i1 = i + 1; i1 < max_n; i1++) {
					if (i1 - i == 2)
						continue;
					c[i1][j + (i1 - i) * (i1 - i)] = true;
				}
			}
		}
	}
}

void input() {
	cin >> n >> k;
}

void get_partition(int i, int j) {
	// cerr << i << " & " << j << endl;
	if (i == 0) {
		assert(j == 0);
		return;
	}
	for (int i1 = 0; i1 < i; i1++) {
		if (i - i1 == 2)
			continue;
		int j1 = j - (i - i1) * (i - i1);
		if (j1 >= 0 && c[i1][j1]) {
			ans.push_back(i - i1);
			get_partition(i1, j1);
			return;
		}
	}
	assert(false);
}

void output() {
	int s = n * n - k * 2;
	if (!c[n][s]) {
		cout << "-1\n";
		return;
	}
	ans.clear();
	get_partition(n, s);
	int start = 0;
	for (size_t i = 0; i < ans.size(); ++i) {
		for (int x = start; x < start + ans[i]; x++) {
			for (int y = x + 1; y < start + ans[i]; y++) {
				cout << x + 1 << ' ' << y + 1 << endl;
			}
		}
		if (start > 0)
			cout << start << ' ' << start + 1 << endl;
		start += ans[i];
	}
}

int main() {
	init();
	input();
	output();
	return 0;
}


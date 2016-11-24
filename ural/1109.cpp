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

const int max_m = 1024, max_n = 1024;

int m, n;
vector<int> a[max_m];
int match[max_n];
bool visit[max_n];
int ans;

void input() {
	int k;
	scanf("%d %d %d", &m, &n, &k);
	for (int x = 0; x < m; x++)
		a[x].clear();
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d", &x, &y); x--; y--;
		a[x].push_back(y);
	}
}

bool search(int x) {
	if (x == -1)
		return true;
	for (size_t k = 0; k < a[x].size(); ++k) {
		int y = a[x][k];
		if (!visit[y]) {
			visit[y] = true;
			if (search(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

void solve() {
	memset(match, -1, sizeof match);
	ans = m + n;
	for (int x = 0; x < m; ++x) {
		memset(visit, 0, sizeof visit);
		if (search(x))
			ans--;
	}
}

void output() {
	printf("%d\n", ans);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


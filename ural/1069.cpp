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

const int MAX_N = 8192;

int prufer[MAX_N], last[MAX_N], succ[MAX_N];
vector<int> a[MAX_N];
int n, m;
int f[MAX_N];
set<int> leaves;

void input() {
	int i;
	m = 0;
	while (scanf("%d", &i) != EOF) {
		prufer[m] = i - 1;
		m++;
	}
	n = m + 1;
}

void solve() {
	memset(last, -1, sizeof last);
	for (int i = m - 1; i >= 0; i--) {
		succ[i] = last[prufer[i]];
		last[prufer[i]] = i;
	}
	leaves.clear();
	for (int i = 0; i < n; i++) {
		if (last[i] == -1)
			leaves.insert(i);
	}
#if 0
	for (set<int>::iterator it = leaves.begin(); it != leaves.end(); it++)
		fprintf(stderr, "%d ", *it);
	fprintf(stderr, "\n");
#endif
	memset(f, -1, sizeof f);
	for (int i = 0; i < m; i++) {
		assert(!leaves.empty());
		int j = *leaves.begin();
		f[j] = prufer[i];
		leaves.erase(leaves.begin());
		if (succ[i] == -1)
			leaves.insert(prufer[i]);
	}
}

void output() {
	for (int i = 0; i < n; i++)
		a[i].clear();
	for (int i = 0; i < n; i++) {
		if (f[i] == -1)
			continue;
		a[i].push_back(f[i]);
		a[f[i]].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		printf("%d:", i + 1);
		sort(a[i].begin(), a[i].end());
		for (size_t k = 0; k < a[i].size(); k++)
			printf(" %d", a[i][k] + 1);
		printf("\n");
	}
}

int main() {
	input();
	solve();
	output();
	return 0;
}


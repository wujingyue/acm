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

const int MAX_N = 1024;
const int oo = 0x7fffffff;

pair<int, int> a[MAX_N];
int target;
int n;
int q[MAX_N], p[MAX_N], step[MAX_N];

void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);
	scanf("%d %d %d", &target, &a[n].first, &a[n].second);
	n++;
}

void solve() {
	memset(p, -1, sizeof p);
	int head, tail;
	head = 0; tail = 1; q[0] = n - 1; p[n - 1] = n - 1; step[n - 1] = 0;
	while (head < tail) {
		int i = q[head];
		for (int j = 0; j < n; j++) {
			if (p[j] == -1 && (a[j].first == a[i].first || a[j].first == a[i].second)) {
				q[tail] = j; tail++;
				p[j] = i;
				step[j] = step[i] + 1;
			}
		}
		head++;
	}
}

void print(int i) {
	if (p[i] == i)
		return;
	print(p[i]);
	printf("%d\n", i + 1);
}

void output() {
	int ans = oo, mi = -1;
	for (int i = 0; i < n; i++) {
		if (p[i] >= 0 && (a[i].first == target || a[i].second == target)) {
			if (step[i] < ans) {
				ans = step[i];
				mi = i;
			}
		}
	}
	if (ans == oo) {
		printf("IMPOSSIBLE\n");
		return;
	}
	printf("%d\n", step[mi]);
	print(mi);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


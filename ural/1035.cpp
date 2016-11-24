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

const int MAX_R = 256;
const int MAX_N = MAX_R * MAX_R * 2;

int R, C, n;
vector<int> a[MAX_N];
int in_deg[MAX_N];
bool visit[MAX_N];
int ans;

int tuple2num(int x, int y, int f) {
	return x * (C + 1) * 2 + y * 2 + f;
}

void add_edge(int face, int x1, int y1, int x2, int y2) {
	int i, j;
	i = tuple2num(x1, y1, face); j = tuple2num(x2, y2, 1 - face);
	a[i].push_back(j); a[j].push_back(i);
	in_deg[i]--; in_deg[j]++;
	i = tuple2num(x2, y2, face); j = tuple2num(x1, y1, 1 - face);
	a[i].push_back(j); a[j].push_back(i);
	in_deg[i]--; in_deg[j]++;
}

void input() {
	scanf("%d %d", &R, &C);
	n = (R + 1) * (C + 1) * 2;
	for (int i = 0; i < n; i++)
		a[i].clear();
	memset(in_deg, 0, sizeof in_deg);
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			char ch;
			do {
				scanf("%c", &ch);
			} while (ch != '.' && ch != '\\' && ch != '/' && ch != 'X');
			if (ch == '\\') {
				add_edge(0, x, y, x + 1, y + 1);
			} else if (ch == '/') {
				add_edge(0, x, y + 1, x + 1, y);
			} else if (ch == 'X') {
				add_edge(0, x, y, x + 1, y + 1);
				add_edge(0, x, y + 1, x + 1, y);
			}
		}
	}
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			char ch;
			do {
				scanf("%c", &ch);
			} while (ch != '.' && ch != '\\' && ch != '/' && ch != 'X');
			if (ch == '\\') {
				add_edge(1, x, y, x + 1, y + 1);
			} else if (ch == '/') {
				add_edge(1, x, y + 1, x + 1, y);
			} else if (ch == 'X') {
				add_edge(1, x, y, x + 1, y + 1);
				add_edge(1, x, y + 1, x + 1, y);
			}
		}
	}
}

int search(int i) {
	visit[i] = true;
	int res = 0;
	if (in_deg[i] > 0)
		res += in_deg[i];
	for (size_t k = 0; k < a[i].size(); k++) {
		int j = a[i][k];
		if (!visit[j])
			res += search(j);
	}
	return res;
}

void solve() {
	ans = 0;
	memset(visit, 0, sizeof visit);
	for (int i = 0; i < n; i++) {
		if (a[i].size() == 0)
			continue;
		if (visit[i])
			continue;
		int sum = search(i);
		if (sum == 0)
			ans++;
		else
			ans += sum;
	}
}

void output() {
	assert(ans % 2 == 0);
	printf("%d\n", ans / 2);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


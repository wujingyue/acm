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

const int max_n = 16384;
const long long OO = 0x7fffffffffffffffLL;
const int oo = 0x7fffffff;

struct Neighbor {
	int y, c, f, g;
	int cost;
	bool back;
};

vector<Neighbor> a[max_n];
int flow[max_n], w[max_n], p[max_n];
long long d[max_n];
int n;
long long ans;
int h[max_n], pos[max_n];
int tail;

void add_edge(int x, int y, int c, int f, long long cost) {
	Neighbor nbx; nbx.y = y; nbx.c = c; nbx.f = f; nbx.g = a[y].size(); nbx.cost = (nbx.f < nbx.c ? 0 : cost); nbx.back = false;
	Neighbor nby; nby.y = x; nby.c = 0; nby.f = -f; nby.g = a[x].size(); nby.cost = (nby.f < nby.c ? 0 : oo); nby.back = true;
	a[x].push_back(nbx); a[y].push_back(nby);
}

void input() {
	scanf("%d", &n);
	for (int x = 1; x <= n; x++)
		a[x].clear();
	memset(flow, 0, sizeof flow);
	for (int x = 1; x <= n; x++) {
		char ch;
		do {
			int y, c, f, cost;
			if (scanf("%d %d %d %d", &y, &c, &f, &cost) == 4) {
				add_edge(x, y, c, f, cost);
				flow[y] += f; flow[x] -= f;
			}
			for (ch = getchar(); ch != ',' && ch != '.'; ch = getchar());
		} while (ch == ',');
	}
	for (int x = 1; x <= n; x++) {
		if (flow[x] < 0)
			add_edge(0, x, oo, -flow[x], 0);
	}
	n++;
}

void go_up(int j) {
	int x = h[j];
	while (j > 0) {
		int i = (j - 1) / 2;
		if (d[h[i]] <= d[x])
			break;
		h[j] = h[i]; pos[h[j]] = j;
		j = i;
	}
	h[j] = x; pos[x] = j;
}

void go_down(int i) {
	int x = h[i];
	while (i * 2 + 1 < tail) {
		int j = i * 2 + 1;
		if (j + 1 < tail && d[h[j + 1]] < d[h[j]])
			j++;
		if (d[x] <= d[h[j]])
			break;
		h[i] = h[j]; pos[h[i]] = i;
		i = j;
	}
	h[i] = x; pos[x] = i;
}

void insert_heap(int x) {
	h[tail] = x; pos[x] = tail; tail++;
	go_up(tail - 1);
}

void pop_heap() {
	pos[h[0]] = -1;
	h[0] = h[tail - 1]; tail--;
	if (tail > 0) {
		pos[h[0]] = 0;
		go_down(0);
	}
}

void solve() {
	for (int x = 0; x < n; x++)
		d[x] = OO;
	memset(pos, -1, sizeof pos);
	d[0] = 0;
	h[0] = 0; pos[0] = 0;
	tail = 1;
	while (tail > 0) {
		int x = h[0];
		for (size_t k = 0; k < a[x].size(); ++k) {
			if (a[x][k].cost == oo)
				continue;
			int y = a[x][k].y;
			long long tmp = d[x] + a[x][k].cost;
			if (tmp < d[y]) {
				d[y] = tmp;
				w[y] = k; p[y] = x;
				if (pos[y] == -1)
					insert_heap(y);
				else
					go_up(pos[y]);
			}
		}
		pop_heap();
	}
	if (d[n - 1] == OO) {
		ans = -1;
		return;
	}
	ans = d[n - 1];
	int y = n - 1;
	while (y != 0) {
		int x = p[y];
		a[x][w[y]].f++; a[x][w[y]].c = max(a[x][w[y]].c, a[x][w[y]].f);
		a[y][a[x][w[y]].g].f--;
		y = x;
	}
}

void output() {
	if (ans == -1)
		printf("Impossible\n");
	else {
		printf("%lld\n", ans);
		for (int x = 1; x < n; x++) {
			bool first = true;
			for (size_t k = 0; k < a[x].size(); ++k) {
				if (a[x][k].back)
					continue;
				if (first)
					first = false;
				else
					printf(", ");
				printf("%d %d", a[x][k].y, a[x][k].f);
			}
			printf(".\n");
		}
	}
}

int main() {
	input();
	solve();
	output();
	return 0;
}


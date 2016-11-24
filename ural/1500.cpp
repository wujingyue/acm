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

const int max_k = 32, max_n = 32, max_r = (1 << 20);

struct Edge {
	int x, y, type;
};

int k, n, m;
vector<pair<int, int> > a[max_n];
bool visit[max_n];
int q[max_n];
int ans;
int cand[max_r], w[max_r], num[max_k];

void input() {
	cin >> k >> n >> m;
	for (int x = 0; x < n; x++)
		a[x].clear();
	for (int i = 0; i < m; i++) {
		int x, y, type;
		cin >> x >> y >> type;
		a[x].push_back(make_pair(y, type));
		a[y].push_back(make_pair(x, type));
	}
}

int weight(int a) {
	int ans = 0;
	for (int i = 0; i < k; i++) {
		if ((a & (1 << i)) > 0)
			ans++;
	}
	return ans;
}

bool by_weight(int a, int b) {
	return weight(a) < weight(b);
}

bool reachable(int s) {
	int head, tail;
	memset(visit, 0, sizeof visit);
	q[0] = 0; head = 0; tail = 1; visit[0] = true;
	while (head < tail) {
		int x = q[head];
		for (int k = (int)a[x].size() - 1; k >= 0; k--) {
			int y = a[x][k].first, type = a[x][k].second;
			if ((s & (1 << type)) > 0 && !visit[y]) {
				q[tail] = y; tail++;
				visit[y] = true;
				if (y == 1)
					return true;
			}
		}
		head++;
	}
	return false;
}

void solve() {
	memset(num, 0, sizeof num);
	for (int s = 1; s < (1 << k); ++s) {
		w[s] = weight(s);
		num[w[s]]++;
	}
	for (int i = 1; i <= k; i++) {
		num[i] += num[i - 1];
	}
	for (int s = 1; s < (1 << k); ++s) {
		num[w[s]]--;
		cand[num[w[s]]] = s;
	}
	for (int i = 0; i < (1 << k) - 1; ++i) {
		if (reachable(cand[i])) {
			ans = cand[i];
			return;
		}
	}
	assert(false);
}

void output() {
	cout << weight(ans) << endl;
	bool first = true;
	for (int i = 0; i < k; ++i) {
		if ((ans & (1 << i)) > 0) {
			if (first)
				first = false;
			else
				cout << ' ';
			cout << i;
		}
	}
	cout << endl;
}

int main() {
	input();
	solve();
	output();
	return 0;
}


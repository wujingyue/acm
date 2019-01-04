/**
 * nodes with degree of 0 may not be connective
 */

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int n = 6;
const int oo = 0x7fffffff;

int ans;
int deg[n], f[n], orig_f[n], orig_deg[n];
vector<pair<int, int> > ans_v;
int m;
int a[n][n];

int root(int x) {
  if (f[x] != x) f[x] = root(f[x]);
  return f[x];
}

void input() {
  scanf("%d", &m);
  memset(deg, 0, sizeof deg);
  for (int x = 0; x < n; x++) f[x] = x;
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    x--;
    y--;
    deg[x]++;
    deg[y]++;
    f[root(y)] = root(x);
  }
}

void search(int x, int y, int cost) {
  if (cost >= ans) return;
  if (x == n - 1) {
    memcpy(f, orig_f, sizeof f);
    memcpy(deg, orig_deg, sizeof deg);
    for (x = 0; x < n; x++) {
      for (y = x + 1; y < n; y++) {
        if (a[x][y] == 0) continue;
        f[root(y)] = root(x);
        deg[x] += a[x][y];
        deg[y] += a[x][y];
      }
    }
    int n_odds = 0;
    int r = -1;
    for (x = 0; x < n; x++) {
      if (deg[x] % 2 != 0) n_odds++;
      if (deg[x] > 0) {
        if (r == -1)
          r = root(x);
        else if (r != root(x))
          return;
      }
    }
    assert(n_odds % 2 == 0);
    if (n_odds > 2) return;
    ans = cost;
    ans_v.clear();
    for (x = 0; x < n; x++) {
      for (y = x + 1; y < n; y++) {
        for (int k = 0; k < a[x][y]; k++) ans_v.push_back(make_pair(x, y));
      }
    }
    return;
  }
  int x1, y1;
  if (y >= n - 1) {
    x1 = x + 1;
    y1 = x1 + 1;
  } else {
    x1 = x;
    y1 = y + 1;
  }
  for (int k = 0; k < 3; k++) {
    a[x][y] = k;
    search(x1, y1, cost + k * (x + y + 2));
  }
}

void solve() {
  memcpy(orig_f, f, sizeof f);
  memcpy(orig_deg, deg, sizeof deg);
#if 0
	for (int x = 0; x < n; x++) {
		fprintf(stderr, "%d: f = %d, deg = %d\n", x, f[x], deg[x]);
	}
#endif
  ans = oo;
  search(0, 1, 0);
}

void output() {
  assert(ans != oo);
  printf("%d\n", ans);
  printf("%u\n", ans_v.size());
  for (size_t i = 0; i < ans_v.size(); i++)
    printf("%d %d\n", ans_v[i].first + 1, ans_v[i].second + 1);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

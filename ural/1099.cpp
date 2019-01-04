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

const int max_n = 256;

vector<int> a[max_n];
bool visit[max_n];
int q[max_n], match[max_n], f[max_n], p[max_n];
bool in_blossom[max_n], in_path[max_n];
int n;
int head, tail;

void input() {
  scanf("%d", &n);
  for (int x = 0; x < n; ++x) a[x].clear();
  int x, y;
  while (scanf("%d %d", &x, &y) != EOF) {
    x--;
    y--;
    a[x].push_back(y);
    a[y].push_back(x);
  }
}

void reset(int x, int z) {
  while (f[x] != z) {
    int y = match[x];
    in_blossom[f[x]] = in_blossom[f[y]] = true;
    x = p[y];
    if (f[x] != z) p[x] = y;
  }
}

int lca(int x, int y) {
  memset(in_path, 0, sizeof in_path);
  while (true) {
    x = f[x];
    in_path[x] = true;
    if (match[x] == -1) break;
    x = p[match[x]];
  }
  while (true) {
    y = f[y];
    if (in_path[y]) return y;
    y = p[match[y]];
  }
}

void contract(int x, int y) {
  int z = lca(x, y);
  memset(in_blossom, 0, sizeof in_blossom);
  reset(x, z);
  reset(y, z);
  if (f[x] != z) p[x] = y;
  if (f[y] != z) p[y] = x;
  for (int x = 0; x < n; ++x) {
    if (in_blossom[f[x]]) {
      f[x] = z;
      if (!visit[x]) {
        q[tail] = x;
        tail++;
        visit[x] = true;
      }
    }
  }
}

bool search(int u) {
  memset(p, -1, sizeof p);
  for (int x = 0; x < n; ++x) f[x] = x;
  memset(visit, 0, sizeof visit);
  head = 0;
  tail = 1;
  q[0] = u;
  visit[u] = true;
  while (head < tail) {
    int x = q[head];
    for (int k = (int)a[x].size() - 1; k >= 0; --k) {
      int y = a[x][k];
      if (f[x] != f[y] && match[x] != y) {
        int x1 = match[y];
        if (y == u || (x1 >= 0 && p[x1] >= 0)) {
          contract(x, y);
        } else if (p[y] == -1) {
          p[y] = x;
          if (x1 == -1) {
            while (y >= 0) {
              x = p[y];
              int y1 = match[x];
              match[x] = y;
              match[y] = x;
              y = y1;
            }
            return true;
          }
          q[tail] = x1;
          tail++;
          visit[x1] = true;
        }
      }
    }
    head++;
  }
  return false;
}

void solve() {
  memset(match, -1, sizeof match);
  for (int x = 0; x < n; x++) {
    if (match[x] == -1) search(x);
  }
}

void output() {
  int ans = 0;
  for (int x = 0; x < n; x++) {
    if (match[x] >= 0) ans++;
  }
  printf("%d\n", ans);
  for (int x = 0; x < n; x++) {
    if (match[x] > x) printf("%d %d\n", x + 1, match[x] + 1);
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

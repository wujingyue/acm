#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int MAX_N = 1024;

vector<int> a[MAX_N];
int match1[MAX_N], match2[MAX_N], p[MAX_N], q[MAX_N];
int m, n;
int ans;

void input() {
  int k;
  scanf("%d %d %d", &m, &n, &k);
  for (int x = 0; x < m; ++x) a[x].clear();
  memset(match1, -1, sizeof match1);
  memset(match2, -1, sizeof match2);
  ans = m + n;
  for (int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    x--;
    y--;
    a[x].push_back(y);
    if (match1[x] == -1 && match2[y] == -1) {
      match1[x] = y;
      match2[y] = x;
      ans--;
    }
  }
}

bool search(int u) {
  memset(p, -1, sizeof p);
  int head = 0, tail = 1;
  q[0] = u;
  p[u] = u;
  while (head < tail) {
    int x = q[head];
    for (size_t k = 0; k < a[x].size(); ++k) {
      int y = a[x][k];
      int x1 = match2[y], y1;
      if (x1 == -1) {
        x1 = p[x];
        y1 = match1[x];
        while (x != u) {
          match1[x] = y;
          match2[y] = x;
          x = x1;
          y = y1;
          x1 = p[x];
          y1 = match1[x];
        }
        match1[x] = y;
        match2[y] = x;
        return true;
      }
      if (p[x1] == -1) {
        q[tail] = x1;
        p[x1] = x;
        tail++;
      }
    }
    head++;
  }
  return false;
}

void solve() {
  for (int x = 0; x < m; x++) {
    if (match1[x] == -1 && search(x)) ans--;
  }
}

void output() { printf("%d\n", ans); }

int main() {
  input();
  solve();
  output();
  return 0;
}

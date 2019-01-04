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

const int max_m = 1024, max_n = 1024;

int m, n;
int a[max_m][max_n], sz[max_m];
int match1[max_n], match2[max_n], p[max_n], q[max_n];
int ans;

void input() {
  int k;
  scanf("%d %d %d", &m, &n, &k);
  memset(sz, 0, sizeof sz);
  memset(match1, -1, sizeof match1);
  memset(match2, -1, sizeof match2);
  ans = m + n;
  // fprintf(stderr, "ans = %d\n", ans);
  for (int i = 0; i < k; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    x--;
    y--;
    a[x][sz[x]] = y;
    sz[x]++;
    if (match1[x] == -1 && match2[y] == -1) {
      match1[x] = y;
      match2[y] = x;
      ans--;
    }
  }
  // fprintf(stderr, "ans = %d\n", ans);
}

bool search(int u) {
  int head, tail;
  memset(p, -1, sizeof p);
  head = 0;
  tail = 1;
  q[0] = u;
  while (head < tail) {
    int x = q[head];
    for (int k = sz[x] - 1; k >= 0; --k) {
      int y = a[x][k], x1 = match2[y];
      if (p[y] == -1) {
        p[y] = x;
        if (x1 == -1) {
          while (y >= 0) {
            x = p[y];
            int y1 = match1[x];
            match1[x] = y;
            match2[y] = x;
            y = y1;
          }
          return true;
        }
        q[tail] = x1;
        tail++;
      }
    }
    head++;
  }
  return false;
}

void solve() {
  // fprintf(stderr, "ans = %d\n", ans);
  for (int x = 0; x < m; ++x) {
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

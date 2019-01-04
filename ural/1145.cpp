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

const int max_r = 820;
const int max_n = max_r * max_r;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int idx[max_r][max_r];
int p[max_n];
bool b[max_r][max_r];
int n, R, C;
int f[max_n], d[max_n], d2[max_n];
int q[max_n];
int head, tail;

inline bool outside(int x, int y) { return x < 0 || x >= R || y < 0 || y >= C; }

void input() {
  cin >> C >> R;
  for (int x = 0; x < R; x++) {
    for (int y = 0; y < C; y++) {
      char ch;
      cin >> ch;
      b[x][y] = (ch == '.');
    }
  }
}

void BFS(int u) {
  memset(f, -1, sizeof f);
  head = 0;
  tail = 1;
  q[0] = 0;
  f[0] = 0;
  while (head < tail) {
    int x = q[head];
    for (int dir = 0; dir < 4; dir++) {
      int x1 = p[x] / C + dx[dir], y1 = p[x] % C + dy[dir];
      if (!outside(x1, y1) && b[x1][y1]) {
        int y = idx[x1][y1];
        if (f[y] == -1) {
          f[y] = x;
          q[tail] = y;
          tail++;
        }
      }
    }
    head++;
  }
}

void compute(int x) {
  d[x] = d2[x] = 0;
  for (int dir = 0; dir < 4; dir++) {
    int x1 = p[x] / C + dx[dir], y1 = p[x] % C + dy[dir];
    if (!outside(x1, y1) && b[x1][y1]) {
      int y = idx[x1][y1];
      if (y != f[x]) {
        if (d[y] + 1 >= d[x]) {
          d2[x] = d[x];
          d[x] = d[y] + 1;
        } else if (d[y] + 1 > d2[x])
          d2[x] = d[y] + 1;
      }
    }
  }
}

void solve() {
  n = 0;
  for (int x = 0; x < R; x++) {
    for (int y = 0; y < C; y++) {
      if (b[x][y]) {
        idx[x][y] = n;
        p[n] = x * C + y;
        n++;
      }
    }
  }
  BFS(0);
  for (int i = tail - 1; i >= 0; i--) compute(q[i]);
}

void output() {
  int ans = 0;
  for (int x = 0; x < n; x++) ans = max(ans, d[x] + d2[x]);
  printf("%d\n", ans);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

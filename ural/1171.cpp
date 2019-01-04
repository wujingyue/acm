#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long double Real;

const Real o = 1e-8;
const Real pi = acos(-1.0);
const int n = 4;
const int max_m = 16;
const int max_s = (1 << (n * n));
const int max_l = max_m * n * n + 1;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const char dir_to_char[] = {'N', 'E', 'S', 'W'};

int m;
int a[max_m][n * n], down[max_m][n * n];
int b[n][n];
bool visited[n][n];
int u;
bool is_cc[max_s];
int ccs[max_s];
int n_ccs;
int sz[max_s];
int c[max_m][n * n][max_l], d[max_m][n * n][max_l];
int f[max_m][n * n][max_l], f_s[max_m][n * n][max_l];
bool valid[max_s][n * n][n * n];
bool mark[n * n][max_s];
int sum[max_s];

void input() {
  scanf("%d", &m);
  for (int i = m - 1; i >= 0; --i) {
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) scanf("%d", &a[i][x * n + y]);
    }
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) scanf("%d", &down[i][x * n + y]);
    }
  }
  int ux, uy;
  scanf("%d %d", &ux, &uy);
  --ux;
  --uy;
  u = ux * n + uy;
}

inline bool outside(int x, int y) { return x < 0 || x >= n || y < 0 || y >= n; }

int dfs(int x, int y) {
  if (visited[x][y]) return 0;
  if (b[x][y] == 0) return 0;
  visited[x][y] = true;
  int res = 1;
  for (int dir = 0; dir < 4; ++dir) {
    int x1 = x + dx[dir], y1 = y + dy[dir];
    if (!outside(x1, y1)) res += dfs(x1, y1);
  }
  return res;
}

bool is_a_cc(int s) {
  int n_filled = 0;
  int ux = -1, uy = -1;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      b[x][y] = s % 2;
      s /= 2;
      if (b[x][y] == 1) {
        n_filled++;
        ux = x;
        uy = y;
      }
    }
  }
  if (n_filled == 0) return true;
  memset(visited, 0, sizeof visited);
  return dfs(ux, uy) == n_filled;
}

void compute_ccs() {
  memset(is_cc, 0, sizeof is_cc);
  n_ccs = 0;
  for (int s = 0; s < max_s; ++s) {
    if (is_a_cc(s)) {
      is_cc[s] = true;
      ccs[n_ccs] = s;
      n_ccs++;
    }
    sz[s] = 0;
    for (int z = 0; z < n * n; ++z) {
      if (s & (1 << z)) sz[s]++;
    }
  }
#if 0
  cerr << "# of ccs = " << n_ccs << endl;
#endif
}

bool update(int &a, int b) {
  if (b > a) {
    a = b;
    return true;
  } else
    return false;
}

void dp() {
  memset(c, -1, sizeof c);
  memset(d, -1, sizeof d);
  c[m - 1][u][1] = a[m - 1][u];
  for (int i = m - 1; i >= 0; --i) {
    for (int s = 0; s < max_s; ++s) {
      sum[s] = 0;
      for (int z = 0; z < n * n; ++z) {
        if (s & (1 << z)) sum[s] += a[i][z];
      }
    }
    // intra-level: c => d
    for (int z = 0; z < n * n; ++z) {
      for (int z1 = 0; z1 < n * n; ++z1) {
        int opt[n * n], opt_s[n * n];
        memset(opt, -1, sizeof opt);
        if (z == z1) {
          opt[0] = 0;
          opt_s[0] = 0;
        } else {
          for (int icc = 0; icc < n_ccs; ++icc) {
            int s = ccs[icc];
            if (!(s & (1 << z))) continue;
            int s1 = (s & (~(1 << z)));
            if (valid[s1][z][z1]) {
              if (update(opt[sz[s] - 1], sum[s1])) opt_s[sz[s] - 1] = s1;
            }
          }
        }
        for (int l = 0; l < max_l; ++l) {
          if (c[i][z][l] < 0) continue;
          for (int delta = 0; delta < n * n; ++delta) {
            if (opt[delta] < 0) continue;
            if (update(d[i][z1][l + delta], c[i][z][l] + opt[delta])) {
              f[i][z1][l + delta] = z;
              f_s[i][z1][l + delta] = opt_s[delta];
            }
          }
        }
      }
    }
    // inter-level: d => c
    if (i > 0) {
      for (int z = 0; z < n * n; ++z) {
        if (down[i][z] == 1) {
          for (int l = 1; l < max_l; ++l) {
            if (d[i][z][l - 1] >= 0)
              c[i - 1][z][l] = d[i][z][l - 1] + a[i - 1][z];
          }
        }
      }
    }
  }
}

void solve() { dp(); }

void print_d(int, int, int);

void print_c(int i, int z, int l) {
  // fprintf(stderr, "print_c(%d, %d, %d)\n", i, z, l);
  if (i == m - 1) return;
  print_d(i + 1, z, l - 1);
  printf("D");
}

bool search(int z, int v, int s, vector<int> &path) {
  assert((s & (1 << z)) == 0);
  if (mark[z][s]) return false;
  mark[z][s] = true;
  if (!is_cc[s]) return false;
  if (z == v) {
    if (s == 0)
      return true;
    else
      return false;
  }
  int x = z / n, y = z % n;
  for (int dir = 0; dir < 4; ++dir) {
    int x1 = x + dx[dir], y1 = y + dy[dir];
    if (!outside(x1, y1)) {
      int z1 = x1 * n + y1;
      if (s & (1 << z1)) {
        bool ret = search(z1, v, (s & (~(1 << z1))), path);
        if (ret) {
          path.push_back(dir);
          return true;
        }
      }
    }
  }
  return false;
}

bool find_path(int u, int v, int s, vector<int> &path) {
  // fprintf(stderr, "find_path(%d, %d, %d)\n", u, v, s);
  assert((s & (1 << u)) == 0);
  memset(mark, 0, sizeof mark);
  bool ret = search(u, v, s, path);
  reverse(path.begin(), path.end());
  return ret;
}

void print_d(int i, int z, int l) {
  // fprintf(stderr, "print_d(%d, %d, %d)\n", i, z, l);
  int z1 = f[i][z][l];
  if (z == z1) {
    print_c(i, z, l);
    return;
  }
  int s = f_s[i][z][l];
  print_c(i, z1, l - sz[s]);
  vector<int> path;
  find_path(z1, z, s, path);
  for (size_t k = 0; k < path.size(); ++k) printf("%c", dir_to_char[path[k]]);
}

void output() {
  Real ans = 0;
#if 0
  for (int i = 0; i < m; ++i) {
    for (int z = 0; z < n * n; ++z) {
      for (int l = 1; l < max_l; ++l) {
        if (d[i][z][l] > 0)
          fprintf(stderr, "d[%d][%d][%d] = %d\n", i, z, l, d[i][z][l]);
      }
    }
  }
#endif
  int ans_z = -1, ans_l = -1;
  for (int z = 0; z < n * n; ++z) {
    for (int l = 1; l < max_l; ++l) {
      Real cur = (Real)d[0][z][l] / l;
      if (cur > ans) {
        ans = cur;
        ans_z = z;
        ans_l = l;
      }
    }
  }
  printf("%.6Lf\n", ans);
  printf("%d\n", ans_l - 1);
  print_d(0, ans_z, ans_l);
  printf("\n");
}

void init() {
  compute_ccs();
  memset(valid, 0, sizeof valid);
  for (int s = 0; s < max_s; ++s) {
    for (int z1 = 0; z1 < n * n; ++z1) {
      for (int z2 = z1 + 1; z2 < n * n; ++z2) {
        int s1 = (s & (~(1 << z1)) & (~(1 << z2)));
        int s2 = (s & (~(1 << z1)));  // no start
        int s3 = (s & (~(1 << z2)));  // no end
        if (!is_cc[s] || !is_cc[s1] || !is_cc[s2] || !is_cc[s3]) {
          valid[s2][z1][z2] = false;
          valid[s2][z2][z1] = false;
          continue;
        }
        if (!(s & (1 << z1)) || !(s & (1 << z2))) {
          valid[s2][z1][z2] = false;
          valid[s2][z2][z1] = false;
          continue;
        }
        vector<int> path;
        valid[s2][z1][z2] = find_path(z1, z2, s2, path);
        valid[s2][z2][z1] = valid[s2][z1][z2];
      }
    }
  }
  cerr << "finished init()\n";
}

int main() {
  init();
  input();
  solve();
  output();
  return 0;
}

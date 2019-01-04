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

typedef long double Real;

const Real o = 1e-8;
const int max_n = 2048;

bool a[max_n][max_n], b[max_n][max_n];
int in_deg[max_n], comp[max_n], finish[max_n];
bool visit[max_n];
int now;
int n, n_comps;
vector<pair<int, int> > r;

void input() {
  scanf("%d", &n);
  memset(a, 0, sizeof a);
  memset(b, 0, sizeof b);
  for (int x = 0; x < n; x++) {
    int y;
    while (true) {
      scanf("%d", &y);
      --y;
      if (y == -1) break;
      a[x][y] = true;
      b[y][x] = true;
    }
  }
}

void dfs1(int x) {
  visit[x] = true;
  for (int y = 0; y < n; y++) {
    if (a[x][y] && !visit[y]) dfs1(y);
  }
  finish[x] = now;
  now++;
}

void dfs2(int x) {
  comp[x] = n_comps;
  for (int y = 0; y < n; y++) {
    if (b[x][y] && comp[y] == -1) dfs2(y);
  }
}

void solve() {
  memset(visit, 0, sizeof visit);
  now = 0;
  for (int x = 0; x < n; x++) {
    if (!visit[x]) dfs1(x);
  }
  r.clear();
  for (int x = 0; x < n; x++) r.push_back(make_pair(finish[x], x));
  sort(r.begin(), r.end(), greater<pair<int, int> >());
  memset(comp, -1, sizeof comp);
  n_comps = 0;
  for (size_t k = 0; k < r.size(); ++k) {
    int x = r[k].second;
    if (comp[x] == -1) {
      dfs2(x);
      n_comps++;
    }
  }
}

void output() {
  memset(in_deg, 0, sizeof in_deg);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (a[x][y] && comp[x] != comp[y]) in_deg[comp[y]]++;
    }
  }
  int n_zeros = 0, the_comp = -1;
  for (int i = 0; i < n_comps; i++) {
    if (in_deg[i] == 0) {
      n_zeros++;
      the_comp = i;
    }
  }
  assert(n_zeros > 0);
  if (n_zeros == 1) {
    for (int x = 0; x < n; x++) {
      if (comp[x] == the_comp) printf("%d ", x + 1);
    }
  }
  printf("0\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

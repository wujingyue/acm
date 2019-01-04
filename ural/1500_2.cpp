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

const int max_k = 32, max_n = 32;

struct Edge {
  int x, y, type;
};

int k, n, m;
vector<Edge> e;
int f[max_n];
int ans;
vector<int> cand;

void input() {
  cin >> k >> n >> m;
  e.clear();
  for (int i = 0; i < m; i++) {
    Edge ee;
    cin >> ee.x >> ee.y >> ee.type;
    e.push_back(ee);
  }
}

int weight(int a) {
  int ans = 0;
  for (int i = 0; i < k; i++) {
    if ((a & (1 << i)) > 0) ans++;
  }
  return ans;
}

bool by_weight(int a, int b) { return weight(a) < weight(b); }

int root(int x) {
  if (f[x] != x) f[x] = root(f[x]);
  return f[x];
}

bool reachable(int s) {
  for (int x = 0; x < n; x++) f[x] = x;
  for (int i = 0; i < m; i++) {
    if ((s & (1 << e[i].type)) > 0) {
      f[root(e[i].x)] = root(e[i].y);
      if (root(0) == root(1)) return true;
    }
  }
  return false;
}

void solve() {
  cand.clear();
  for (int s = 1; s < (1 << k); ++s) cand.push_back(s);
  sort(cand.begin(), cand.end(), by_weight);
  for (size_t i = 0; i < cand.size(); ++i) {
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

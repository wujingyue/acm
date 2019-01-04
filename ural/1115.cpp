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

const int max_n = 128, max_m = 32, max_r = 16384;

int m, n;
int a[max_n], b[max_m];
bool c[max_n][max_r];
int t[max_n];

void input() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
}

bool search(int i) {
  if (i == -1) return true;
  for (int j = 0; j < m; j++) {
    if (!c[i][b[j]]) return false;
  }
  for (int j = 0; j < m; j++) {
    if (b[j] == a[i]) {
      b[j] -= a[i];
      t[i] = j;
      if (search(i - 1)) return true;
      b[j] += a[i];
      return false;
    }
  }
  for (int j = 0; j < m; j++) {
    if (b[j] >= a[i]) {
      b[j] -= a[i];
      t[i] = j;
      if (search(i - 1)) return true;
      b[j] += a[i];
    }
  }
  return false;
}

void solve() {
  sort(a, a + n);
  memset(c, 0, sizeof c);
  for (int i = 0; i < n; i++) {
    c[i][0] = true;
    if (i == 0) {
      c[i][a[i]] = true;
      continue;
    }
    for (int j = 0; j < max_r; j++) {
      if (c[i - 1][j]) {
        c[i][j] = true;
        c[i][j + a[i]] = true;
      }
    }
  }
  bool ret = search(n - 1);
  assert(ret);
}

void output() {
  vector<int> ans[max_m];
  for (int i = 0; i < n; i++) ans[t[i]].push_back(a[i]);
  for (int i = 0; i < m; i++) {
    cout << ans[i].size() << endl;
    for (size_t j = 0; j < ans[i].size(); ++j) {
      if (j > 0) cout << ' ';
      cout << ans[i][j];
    }
    cout << endl;
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

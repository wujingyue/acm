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
const Real pi = acos(-1.0);

const int max_n = 1024;

vector<int> a[max_n];
vector<int> t;
int n, u;
vector<int> ans;

void input() {
  scanf("%d %d", &n, &u);
  u--;
  for (int x = 0; x < n; x++) a[x].clear();
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      int k;
      scanf("%d", &k);
      if (x != y && k == 0) a[y].push_back(x);
    }
  }
}

void solve() {
  ans.clear();
  t.clear();
  t.push_back(u);
  while (!t.empty()) {
    int x = t.back();
    if (!a[x].empty()) {
      int y = a[x].back();
      a[x].pop_back();
      t.push_back(y);
    } else {
      ans.push_back(x);
      t.pop_back();
    }
  }
}

void output() {
  for (size_t i = 0; i + 1 < ans.size(); ++i)
    printf("%d %d\n", ans[i] + 1, ans[i + 1] + 1);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

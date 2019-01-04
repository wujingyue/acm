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

const int n = 16, m = (1 << n);
const Real PI = acos(-1.0);
const Real o = 1e-8;
const Real R = 0.4;

struct Point {
  Real x, y;
};

Point p[n];
bool ans;
vector<Real> X;
pair<Real, Real> a[n][n];
int c[m][2];
vector<int> shoot[n];

void input() {
  for (int i = 0; i < n; i++) scanf("%Lf %Lf", &p[i].x, &p[i].y);
}

Real normalize(Real a) {
  while (a < -PI) a += PI * 2;
  while (a >= PI) a -= PI * 2;
  return a;
}

void my_unique(vector<Real> &X) {
  size_t k = 0, i = 0;
  while (i < X.size()) {
    size_t j = i + 1;
    while (j < X.size() && abs(X[j] - X[i]) <= o) j++;
    X[k] = X[i];
    k++;
    i = j;
  }
  X.resize(k);
}

bool inside(Real a, Real b, Real c) {
  if (b <= c + o) return b <= a + o && a <= c + o;
  return inside(a, b, PI) || inside(a, -PI, c);
}

int get_removed(int i, Real th) {
  int removed = (1 << i);
  for (int j = 0; j < n; j++) {
    if (i == j) continue;
    if (inside(th, a[i][j].first, a[i][j].second)) removed |= (1 << j);
  }
  return removed;
}

bool get_c(int s, int turn) {
  if (c[s][turn] >= 0) return c[s][turn] == 1;
  c[s][turn] = 0;
  int low = turn * n / 2, high = low + n / 2;
  for (int i = low; i < high; i++) {
    if ((s & (1 << i)) == 0) continue;
    for (size_t k = 0; k < shoot[i].size(); ++k) {
      int s1 = s & ((1 << n) - 1 - shoot[i][k]);
      if (get_c(s1, 1 - turn) == false) {
        c[s][turn] = 1;
        return true;
      }
    }
  }
  return false;
}

Real dist(const Point &a, const Point &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Real middle(Real a, Real b) {
  if (a <= b + o) return (a + b) / 2;
  return normalize((a + b + PI * 2) / 2);
}

void solve() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      Real al = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
      Real th = asin(R * 2 / dist(p[i], p[j]));
      a[i][j].first = normalize(al - th);
      a[i][j].second = normalize(al + th);
    }
  }
  for (int i = 0; i < n; i++) {
    X.clear();
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      X.push_back(a[i][j].first);
      X.push_back(a[i][j].second);
    }
    sort(X.begin(), X.end());
    my_unique(X);
    assert(X.size() > 0);
    X.push_back(X[0]);
    shoot[i].clear();
    for (size_t k = 0; k + 1 < X.size(); k++) {
      shoot[i].push_back(get_removed(i, X[k]));
      shoot[i].push_back(get_removed(i, middle(X[k], X[k + 1])));
    }
    sort(shoot[i].begin(), shoot[i].end());
    shoot[i].resize(unique(shoot[i].begin(), shoot[i].end()) -
                    shoot[i].begin());
  }
  memset(c, -1, sizeof c);
  c[0][0] = 0;
  c[0][1] = 0;
  ans = get_c((1 << n) - 1, 0);
}

void output() {
  if (ans)
    printf("RED\n");
  else
    printf("WHITE\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

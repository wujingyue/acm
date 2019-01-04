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

const int MAX_N = 64;
const Real PI = acos(-1.0);

struct Point {
  Real x, y;
};

Point m[MAX_N], a[MAX_N];
Real al[MAX_N];
Real x0, Y0;
int n;

inline Real multi(Real x1, Real y1, Real x2, Real y2) {
  return x1 * y2 - x2 * y1;
}

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%Lf %Lf", &m[i].x, &m[i].y);
  for (int i = 0; i < n; i++) {
    scanf("%Lf", &al[i]);
    al[i] = al[i] * PI / 180;
  }
}

void solve() {
  Real a1, b1, c1, a2, b2, c2;
  a1 = 1;
  b1 = 0;
  c1 = 0;
  a2 = 0;
  b2 = 1;
  c2 = 0;
  for (int i = 1; i <= n; i++) {
    Real A1, B1, C1, A2, B2, C2;
    Real th = al[i - 1];
    c1 -= m[i - 1].x;
    c2 -= m[i - 1].y;
    A1 = a1 * cos(th) - a2 * sin(th);
    B1 = b1 * cos(th) - b2 * sin(th);
    C1 = c1 * cos(th) - c2 * sin(th);
    A2 = a2 * cos(th) + a1 * sin(th);
    B2 = b2 * cos(th) + b1 * sin(th);
    C2 = c2 * cos(th) + c1 * sin(th);
    C1 += m[i - 1].x;
    C2 += m[i - 1].y;
    a1 = A1;
    b1 = B1;
    c1 = C1;
    a2 = A2;
    b2 = B2;
    c2 = C2;
  }
  x0 = multi(b1, c1, b2 - 1, c2) / multi(a1 - 1, b1, a2, b2 - 1);
  Y0 = multi(c1, a1 - 1, c2, a2) / multi(a1 - 1, b1, a2, b2 - 1);
}

void output() {
  a[0].x = x0;
  a[0].y = Y0;
  for (int i = 1; i < n; i++) {
    a[i].x = (a[i - 1].x - m[i - 1].x) * cos(al[i - 1]) -
             (a[i - 1].y - m[i - 1].y) * sin(al[i - 1]) + m[i - 1].x;
    a[i].y = (a[i - 1].x - m[i - 1].x) * sin(al[i - 1]) +
             (a[i - 1].y - m[i - 1].y) * cos(al[i - 1]) + m[i - 1].y;
  }
  for (int i = 0; i < n; i++) printf("%.2Lf %.2Lf\n", a[i].x, a[i].y);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

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
const int max_n = 8192;
const Real o = 1e-8;

struct Point {
  Real x, y;
};
Point operator-(const Point &a, const Point &b) {
  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return c;
}

int n;
Point p[max_n];
vector<pair<Real, int> > r;

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%Lf %Lf", &p[i].x, &p[i].y);
}

Real dist2(const Point &a, const Point &b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

Real dist(const Point &a, const Point &b) { return sqrt(dist2(a, b)); }

Real get_angle(const Point &A, const Point &B, const Point &C) {
  Real a2, b2, c2, a, b;
  a2 = dist2(B, C);
  b2 = dist2(A, C);
  c2 = dist2(A, B);
  a = dist(B, C);
  b = dist(A, C);
  return (a2 + b2 - c2) / a / b / 2;
}

Real cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

Real area(const Point &a, const Point &b, const Point &c) {
  return cross(b - a, c - a);
}

void solve() {
  if (n % 2 == 0) {
    printf("No solution\n");
    return;
  }
  for (int i = 1; i < n; i++) {
    if (p[i].y < p[0].y - o || (p[i].y <= p[0].y + o && p[i].x < p[0].y))
      swap(p[0], p[i]);
  }
  for (int i = 2; i < n; i++) {
    if (area(p[0], p[1], p[i]) > o) swap(p[1], p[i]);
  }
  r.clear();
  for (int i = 2; i < n; i++) {
    r.push_back(make_pair(get_angle(p[0], p[1], p[i]), i));
  }
  sort(r.begin(), r.end());
  int k = r[(n - 3) / 2].second;
  printf("%.0Lf %.0Lf\n%.0Lf %.0Lf\n%.0Lf %.0Lf\n", p[0].x, p[0].y, p[1].x,
         p[1].y, p[k].x, p[k].y);
}

void output() {}

int main() {
  input();
  solve();
  output();
  return 0;
}

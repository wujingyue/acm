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

const int max_n = 512;

struct Point {
  int x, y;
};
Point operator-(const Point &a, const Point &b) {
  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return c;
}

int cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

Real dist(const Point &a, const Point &b) {
  return sqrt(
      (long double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

Real ans;
int n;
Point p[max_n];

void input() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
}

void solve() {
  ans = 0.0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      bool online = false;
      for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;
        if (cross(p[i] - p[k], p[j] - p[k]) == 0 &&
            p[k].x >= min(p[i].x, p[j].x) && p[k].x <= max(p[i].x, p[j].x) &&
            p[k].y >= min(p[i].y, p[j].y) && p[k].y <= max(p[i].y, p[j].y)) {
          online = true;
          break;
        }
      }
      if (!online) ans += dist(p[i], p[j]);
    }
  }
}

void output() { printf("%.0Lf\n", ans); }

int main() {
  input();
  solve();
  output();
  return 0;
}

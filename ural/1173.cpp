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

struct Point {
  Real x, y, th, dis;
  int id;
};
bool operator<(const Point &a, const Point &b) {
  return a.th < b.th - o || a.th <= b.th + o && a.dis < b.dis;
}

Point p[max_n];
Real ux, uy;
int n;
bool ans;

inline Real sqr(Real a) { return a * a; }

void input() {
  scanf("%Lf %Lf", &ux, &uy);
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%Lf %Lf %d\n", &p[i].x, &p[i].y, &p[i].id);
    assert(abs(p[i].x - ux) > o || abs(p[i].y - uy) > o);
  }
}

void solve() {
  for (int i = 0; i < n; i++) {
    p[i].th = atan2(p[i].y - uy, p[i].x - ux);
    p[i].dis = sqrt(sqr(p[i].x - ux) + sqr(p[i].y - uy));
  }
  sort(p, p + n);
  if (abs(p[0].th - p[n - 1].th) <= o) {
    ans = false;
    return;
  }
  ans = true;
  int i = n - 1;
  while (i >= 0 && abs(p[i].th - p[n - 1].th) <= o) i--;
  assert(i >= 0);
  reverse(p + i + 1, p + n);
}

void output() {
  if (!ans) {
    printf("-1\n");
    return;
  }
  printf("0\n");
  for (int i = 0; i < n; i++) printf("%d\n", p[i].id);
  printf("0\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

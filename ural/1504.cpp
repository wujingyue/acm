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

const Real o = 1e-8, PI = acos(-1.0);
const int max_n = 1024;

struct Point {
  Real x, y;
  int w;
  Point(Real xx = 0.0, Real yy = 0.0) : x(xx), y(yy) {}
};
struct Event {
  Real x;
  int type;
  Event(Real xx, int tt) : x(xx), type(tt) {}
};
bool operator<(const Event &a, const Event &b) {
  return a.x < b.x - o || (a.x <= b.x + o && a.type > b.type);
}

Real R;
int n;
Point p[max_n];
vector<Event> e;
Real ans;

void input() {
  cin >> R >> n;
  for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y >> p[i].w;
}

bool by_weight(const Point &a, const Point &b) { return a.w > b.w; }

void get_inter(const Point &a, const Point &b, Real &t1, Real &t2) {
  Real K, B, aa, bb, cc, dd;
  if (abs(a.x - b.x) > o) {
    K = -(2 * a.y - 2 * b.y) / (2 * a.x - 2 * b.x);
    B = (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y) / (2 * a.x - 2 * b.x);
    aa = K * K + 1;
    bb = 2 * K * B;
    cc = B * B - R * R;
    dd = bb * bb - 4 * aa * cc;
    assert(dd > o);
    Real y1 = (-bb + sqrt(dd)) / aa / 2, y2 = (-bb - sqrt(dd)) / aa / 2;
    Real x1 = K * y1 + B, x2 = K * y2 + B;
    t1 = atan2(y1, x1);
    t2 = atan2(y2, x2);
  } else {
    assert(abs(a.y - b.y) > o);
    K = -(2 * a.x - 2 * b.x) / (2 * a.y - 2 * b.y);
    B = (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y) / (2 * a.y - 2 * b.y);
    aa = K * K + 1;
    bb = 2 * K * B;
    cc = B * B - R * R;
    dd = bb * bb - 4 * aa * cc;
    assert(dd > 0);
    Real x1 = (-bb + sqrt(dd)) / aa / 2, x2 = (-bb - sqrt(dd)) / aa / 2;
    Real y1 = K * x1 + B, y2 = K * x2 + B;
    t1 = atan2(y1, x1);
    t2 = atan2(y2, x2);
  }
}

inline Real sqr(Real a) { return a * a; }

inline Real dist(const Point &a, const Point &b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void solve() {
  sort(p, p + n, by_weight);
  for (int i = 0; i < n; i++) {
    e.clear();
    for (int j = i + 1; j < n; j++) {
      Real t1, t2;
      get_inter(p[i], p[j], t1, t2);
      if (t1 > t2) swap(t1, t2);
      Real a1 = (t1 + t2) / 2;
      if (dist(p[i], Point(R * cos(a1), R * sin(a1))) <
          dist(p[j], Point(R * cos(a1), R * sin(a1)))) {
        e.push_back(Event(t1, 1));
        e.push_back(Event(t2, 0));
      } else {
        e.push_back(Event(-PI, 1));
        e.push_back(Event(t1, 0));
        e.push_back(Event(t2, 1));
        e.push_back(Event(PI, 0));
      }
    }
    sort(e.begin(), e.end());
    int num = 0;
    for (size_t k = 0; k < e.size(); ++k) {
      if (e[k].type == 1) {
        num++;
        if (num == n - i - 1) {
          ans = e[k].x;
          return;
        }
      } else
        num--;
    }
  }
  assert(false);
}

void output() {
  printf("%.7Lf %.7Lf\n", R * cos(ans), R * sin(ans));
  /*
  Real min_d = 1e+20;
  int max_w = 0;
  for (int i = 0; i < n; i++) {
          Real d = dist(Point(R * cos(ans), R * sin(ans)), p[i]);
          fprintf(stderr, "%.9Lf %d\n", d, p[i].w);
          if (d < min_d - o || (d <= min_d + o && p[i].w > max_w)) {
                  min_d = d;
                  max_w = p[i].w;
          }
  }
  fprintf(stderr, "%d\n", max_w);
  */
}

int main() {
  input();
  solve();
  output();
  return 0;
}

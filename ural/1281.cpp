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

const int max_m = 16;
const int max_n = 1024;
const Real o = 1e-8;

struct Point {
  Real x, y;
  Point(Real xx, Real yy) : x(xx), y(yy) {}
};

Real cross(Real x1, Real y1, Real x2, Real y2) { return x1 * y2 - x2 * y1; }

Real dist(Real x1, Real y1, Real x2, Real y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool prev(const Point &a, const Point &b, const Point &c) {
  Real mul = cross(a.x - c.x, a.y - c.y, b.x - c.x, b.y - c.y);
  return mul > o || (mul >= -o &&
                     dist(a.x, a.y, c.x, c.y) >= dist(b.x, b.y, c.x, c.y) - o);
}

bool equal(const Point &a, const Point &b) {
  return abs(a.x - b.x) <= o && abs(a.y - b.y) <= o;
}

struct by_slope {
  Point c;
  by_slope(const Point &cc) : c(cc) {}
  bool operator()(const Point &a, const Point &b) {
    Real mul = cross(a.x - c.x, a.y - c.y, b.x - c.x, b.y - c.y);
    return mul > o ||
           (mul >= -o && dist(a.x, a.y, c.x, c.y) < dist(b.x, b.y, c.x, c.y));
  }
};

vector<Point> river[max_m];
vector<Point> p;
bool visit[max_m];
int m;
bool a[max_m][max_m];
int t[max_n];
Real ans;

void input() {
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    river[i].clear();
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      Real x, y;
      scanf("%Lf %Lf", &x, &y);
      river[i].push_back(Point(x, y));
    }
  }
}

void search(int i) {
  visit[i] = true;
  for (size_t k = 0; k < river[i].size(); ++k) p.push_back(river[i][k]);
  for (int j = 0; j < m; j++) {
    if (!visit[j] && a[i][j]) search(j);
  }
}

Real convex_hull(vector<Point> &p) {
  int n = p.size();
  if (n <= 2) return 0;
  for (int i = 1; i < n; i++) {
    if (p[i].y < p[0].y - o || (p[i].y <= p[0].y + o && p[i].x < p[0].x))
      swap(p[0], p[i]);
  }
  sort(p.begin() + 1, p.end(), by_slope(p[0]));
#if 0
	for (int i = 0; i < n; i++) {
		fprintf(stderr, "%Lf %Lf\n", p[i].x, p[i].y);
	}
	fprintf(stderr, "----------\n");
#endif
  int top = 2;
  t[0] = 0;
  t[1] = 1;
  for (int j = 2; j < n; j++) {
    while (top >= 2 && prev(p[j], p[t[top - 1]], p[t[top - 2]])) top--;
    t[top] = j;
    top++;
  }
#if 0
	for (int i = 0; i < top; i++)
		fprintf(stderr, "%d\n", t[i]);
	fprintf(stderr, "-----------\n");
#endif
  Real area = 0;
  for (int i = 1; i + 1 < top; i++) {
    area = area + cross(p[t[i]].x - p[t[0]].x, p[t[i]].y - p[t[0]].y,
                        p[t[i + 1]].x - p[t[0]].x, p[t[i + 1]].y - p[t[0]].y);
  }
  return abs(area) / 2;
}

bool online(const Point &c, const Point &a, const Point &b) {
  Real mul = cross(a.x - c.x, a.y - c.y, b.x - c.x, b.y - c.y);
  if (abs(mul) > o) return false;
  return min(a.x, b.x) <= c.x + o && c.x <= max(a.x, b.x) + o &&
         min(a.y, b.y) <= c.y + o && c.y <= max(a.y, b.y) + o;
}

void solve() {
  memset(a, 0, sizeof a);
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      for (size_t k1 = 0; k1 < river[i].size(); ++k1) {
        for (size_t k2 = 0; k2 < river[j].size(); ++k2) {
          if (equal(river[i][k1], river[j][k2])) {
            a[i][j] = a[j][i] = true;
            break;
          }
        }
      }
    }
  }
  memset(visit, 0, sizeof visit);
  ans = 0;
  for (int i = 0; i < m; i++) {
    if (!visit[i]) {
      p.clear();
      search(i);
      Real area = convex_hull(p);
      ans = max(ans, area);
    }
  }
}

void output() { printf("%.2Lf\n", ans); }

int main() {
  input();
  solve();
  output();
  return 0;
}

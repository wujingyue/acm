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

const int max_n = 64;
const int max_k = 1024;
const Real o = 1e-8;
const int oo = 0x7fffffff;

struct Radio {
  int x, y;
  Real r;
};

int m, n, k;
Radio radio[max_k];
Real h[max_n][max_n];
int low[max_n][max_n], high[max_n][max_n];

inline Real sqr(Real x) { return x * x; }

inline Real dist(Real x1, Real y1, Real x2, Real y2) {
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

void input() {
  cin >> m >> n >> k;
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) cin >> h[x][y];
  }
  for (int i = 0; i < k; i++) {
    cin >> radio[i].x >> radio[i].y >> radio[i].r;
    radio[i].x--;
    radio[i].y--;
  }
}

int my_round(Real a) {
  if (abs(a) <= o) return 0;
  if (a > 0) return (int)(a + 0.5);
  return -(int)(-a + 0.5);
}

int my_floor(Real a) {
  int a1 = my_round(a);
  if (abs(a - a1) <= o)
    return a1;
  else
    return my_round(floor(a));
}

int my_ceil(Real a) {
  int a1 = my_round(a);
  if (abs(a - a1) <= o)
    return a1;
  else
    return my_round(ceil(a));
}

void solve() {
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) {
      low[x][y] = (int)(h[x][y] + 0.5);
      high[x][y] = oo;
    }
  }
  for (int i = 0; i < k; i++) {
    for (int x = 0; x < m; x++) {
      for (int y = 0; y < n; y++) {
        if (x == radio[i].x && y == radio[i].y) {
          low[x][y] = oo;
          high[x][y] = -oo;
          continue;
        }
        Real d = dist(x, y, radio[i].x, radio[i].y);
        if (radio[i].r < d - o) {
          low[x][y] = oo;
          high[x][y] = -oo;
          continue;
        }
        Real dh = sqrt(abs(sqr(radio[i].r) - sqr(d)));
        low[x][y] = max(low[x][y], my_ceil(h[radio[i].x][radio[i].y] - dh));
        high[x][y] = min(high[x][y], my_floor(h[radio[i].x][radio[i].y] + dh));
        // fprintf(stderr, "%d - (%d, %d), %Lf +/- %Lf\n", i, x, y,
        // h[radio[i].x][radio[i].y], dh);
      }
    }
  }
}

void output() {
  int ans = 0;
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) {
      if (low[x][y] <= high[x][y]) {
        ans += high[x][y] - low[x][y] + 1;
        // fprintf(stderr, "(%d %d) [%d, %d]\n", x, y, low[x][y], high[x][y]);
      }
    }
  }
  cout << ans << endl;
}

int main() {
  input();
  solve();
  output();
  return 0;
}

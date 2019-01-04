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
typedef complex<Real> Comp;

const Real o = 1e-4;

int n;
vector<Comp> p;
vector<Comp> dots[16][16];
vector<pair<int, int> > ans;

void input() {
  cin >> n;
  p.clear();
  for (int i = 0; i < n; i++) {
    Real x, y;
    cin >> x >> y;
    p.push_back(Comp(x, y));
  }
  assert(p.size() == (size_t)n);
}

void add_points(int num, Real sx, Real sy, vector<Comp> &a) {
  if (num == 0) return;
  if (num == 1) {
    a.push_back(Comp(sx + 2, sy + 2));
    return;
  }
  if (num == 2) {
    a.push_back(Comp(sx + 1, sy + 1));
    a.push_back(Comp(sx + 3, sy + 3));
    return;
  }
  if (num == 3) {
    a.push_back(Comp(sx + 1, sy + 1));
    a.push_back(Comp(sx + 2, sy + 2));
    a.push_back(Comp(sx + 3, sy + 3));
    return;
  }
  if (num == 4) {
    a.push_back(Comp(sx + 1, sy + 1));
    a.push_back(Comp(sx + 1, sy + 3));
    a.push_back(Comp(sx + 3, sy + 1));
    a.push_back(Comp(sx + 3, sy + 3));
    return;
  }
  if (num == 5) {
    a.push_back(Comp(sx + 1, sy + 1));
    a.push_back(Comp(sx + 1, sy + 3));
    a.push_back(Comp(sx + 3, sy + 1));
    a.push_back(Comp(sx + 3, sy + 3));
    a.push_back(Comp(sx + 2, sy + 2));
    return;
  }
  if (num == 6) {
    a.push_back(Comp(sx + 1, sy + 1));
    a.push_back(Comp(sx + 1, sy + 3));
    a.push_back(Comp(sx + 3, sy + 1));
    a.push_back(Comp(sx + 3, sy + 3));
    a.push_back(Comp(sx + 2, sy + 1));
    a.push_back(Comp(sx + 2, sy + 3));
    return;
  }
  assert(false);
}

void construct(int i1, int i2) {
  dots[i1][i2].clear();
  add_points(i1, 0, 0, dots[i1][i2]);
  add_points(i2, 4, 0, dots[i1][i2]);
  for (size_t i = 0; i < dots[i1][i2].size(); ++i)
    dots[i1][i2][i] -= real(dots[i1][i2][i]) * 2;
#if 0
	cerr << "dots " << i1 << ' ' << i2 << endl;
	for (size_t i = 0; i < dots[i1][i2].size(); ++i)
		cerr << dots[i1][i2][i] << endl;
#endif
}

bool match(vector<Comp> &a, vector<Comp> &b) {
  assert(a.size() == b.size());
  if (a.size() == 0 || a.size() == 1) return true;
  Comp ca, cb;
  for (int i = 0; i < n; i++) {
    ca += a[i];
    cb += b[i];
  }
  ca /= n;
  cb /= n;
  // cerr << ca << ' ' << cb << endl;
  int i = 0;
  while (abs(real(a[i]) - real(ca)) <= o && abs(imag(a[i]) - imag(ca)) <= o)
    i++;
  // cerr << "i = " << i << endl;
  for (int j = 0; j < n; j++) {
    if (abs(real(b[j]) - real(cb)) <= o && abs(imag(b[j]) - imag(cb)) <= o)
      continue;
    Comp rotate = (b[j] - cb) / (a[i] - ca);
    if (abs(rotate) * 4 < 1 - o || abs(rotate) * 4 > 100 + o) continue;
    // cerr << "j = " << j << endl;
    // cerr << "rotate = " << rotate << endl;
    bool ok = true;
    for (int k = 0; k < n; k++) {
      Comp target = (a[k] - ca) * rotate + cb;
      // cerr << a[k] << " -> " << target << endl;
      bool found = false;
      for (int k1 = 0; k1 < n; k1++) {
        if (abs(real(target) - real(b[k1])) <= o &&
            abs(imag(target) - imag(b[k1])) <= o) {
          found = true;
          break;
        }
      }
      if (!found) {
        ok = false;
        break;
      }
    }
    if (ok) return true;
  }
  return false;
}

void solve() {
  for (int i1 = 0; i1 <= 6; i1++) {
    for (int i2 = i1; i2 <= 6; i2++) {
      construct(i1, i2);
    }
  }
  ans.clear();
  for (int i1 = 0; i1 <= 6; i1++) {
    for (int i2 = i1; i2 <= 6; i2++) {
      if (i1 + i2 != n) continue;
      // cerr << i1 << ' ' << i2 << endl;
      if (match(dots[i1][i2], p)) {
        ans.push_back(make_pair(i1, i2));
      }
    }
  }
}

void output() {
  sort(ans.begin(), ans.end());
  for (size_t i = 0; i < ans.size(); ++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

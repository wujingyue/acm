/**
 * while >= 24 -= 24
 */

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

int h1, m1, h2, m2, h3, m3, h4, m4;

void input() {
  scanf("%d.%d %d.%d %d.%d %d.%d", &h1, &m1, &h2, &m2, &h3, &m3, &h4, &m4);
}

int duration(int h1, int m1, int h2, int m2) {
  int res = (h2 - h1) * 60 + (m2 - m1);
  while (res < 0) res += 24 * 60;
  while (res >= 24 * 60) res -= 24 * 60;
  return res;
}

void solve() {
  for (int diff = -5; diff <= 5; diff++) {
    h2 += diff;
    h3 += diff;
    int d1 = duration(h1, m1, h2, m2);
    int d2 = duration(h3, m3, h4, m4);
    if (d1 <= 360 && d2 <= 360 && abs(d1 - d2) <= 10) {
      printf("%d\n", abs(diff));
      return;
    }
    h2 -= diff;
    h3 -= diff;
  }
  assert(false);
}

void output() {}

int main() {
  input();
  solve();
  output();
  return 0;
}

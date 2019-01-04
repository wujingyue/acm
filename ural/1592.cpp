/**
 * some clocks are the same
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

const int max_n = 65536;

int n;
int a[max_n], b[max_n];
int ans, mi;

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int hh, mm, ss;
    scanf("%d:%d:%d", &hh, &mm, &ss);
    if (hh == 12) hh = 0;
    a[i] = hh * 3600 + mm * 60 + ss;
  }
}

void solve() {
  sort(a, a + n);
  b[n - 1] = 1;
  for (int i = n - 2; i >= 0; i--) {
    if (a[i] == a[i + 1])
      b[i] = b[i + 1] + 1;
    else
      b[i] = 1;
  }
  int cur = 0;
  for (int i = 0; i < n - 1; i++) cur += a[n - 1] - a[i];
  ans = cur;
  mi = n - 1;
  for (int i = n - 2; i >= 0; i--) {
    if (a[i + 1] == a[i]) continue;
    cur += b[i + 1] * 12 * 3600 - n * (a[i + 1] - a[i]);
    if (cur < ans) {
      ans = cur;
      mi = i;
    }
  }
}

void output() {
  int hh, mm, ss;
  hh = a[mi] / 3600;
  mm = a[mi] / 60 % 60;
  ss = a[mi] % 60;
  if (hh == 0) hh = 12;
  printf("%d:%02d:%02d\n", hh, mm, ss);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

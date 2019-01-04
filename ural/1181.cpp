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

int n;
int a[max_n];
int f[max_n][max_n], c[max_n][max_n];
int next[max_n][3], prev[max_n][3];

void input() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    char ch;
    cin >> ch;
    if (ch == 'R')
      a[i] = 0;
    else if (ch == 'G')
      a[i] = 1;
    else
      a[i] = 2;
  }
}

void solve() {
  prev[0][0] = prev[0][1] = prev[0][2] = -1;
  for (int i = 1; i < n; i++) {
    for (int k = 0; k < 3; k++) prev[i][k] = prev[i - 1][k];
    prev[i][a[i - 1]] = i - 1;
  }
  next[n - 1][0] = next[n - 1][1] = next[n - 1][2] = n;
  for (int i = n - 2; i >= 0; i--) {
    for (int k = 0; k < 3; k++) next[i][k] = next[i + 1][k];
    next[i][a[i + 1]] = i + 1;
  }
  for (int i = 0; i + 1 < n; i++) {
    c[i][i + 1] = (a[i] != a[i + 1]);
  }
  for (int s = 2; s < n; s++) {
    for (int i = 0; i + s < n; i++) {
      int j = i + s;
      if (a[i] == a[j]) {
        c[i][j] = false;
        continue;
      }
      int color = 3 - a[i] - a[j];
      int k;
      k = next[i][color];
      if (k < j) {
        if (c[i][k] && c[k][j]) {
          c[i][j] = true;
          f[i][j] = k;
          continue;
        }
      }
      k = prev[j][color];
      if (k > i) {
        if (c[i][k] && c[k][j]) {
          c[i][j] = true;
          f[i][j] = k;
          continue;
        }
      }
      c[i][j] = false;
    }
  }
}

void print(int i, int j) {
  assert(i <= j);
  if (j - i <= 2) return;
  int k = f[i][j];
  if (k - i >= 2) {
    printf("%d %d\n", i + 1, k + 1);
    print(i, k);
  }
  if (j - k >= 2) {
    printf("%d %d\n", k + 1, j + 1);
    print(k, j);
  }
}

void output() {
  if (!c[0][n - 1]) {
    printf("0\n");
    return;
  }
  printf("%d\n", n - 3);
  print(0, n - 1);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

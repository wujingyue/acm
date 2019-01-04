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

const int M = 100000000;
const int max_n = 65536;

int a[max_n];
int n;

struct BigInt {
  int sign;
  int len;
  int digit[5000];
  BigInt() {
    memset(digit, 0, sizeof digit);
    len = 1;
    sign = 1;
  }
};
BigInt ans;

bool operator<(const BigInt &a, const BigInt &b) {
  if (a.sign != b.sign) return a.sign < b.sign;
  if (a.sign == 1) {
    if (a.len != b.len) return a.len < b.len;
    for (int i = a.len - 1; i >= 0; i--) {
      if (a.digit[i] < b.digit[i]) return true;
      if (a.digit[i] > b.digit[i]) return false;
    }
    return false;
  } else {
    if (a.len != b.len) return a.len > b.len;
    for (int i = a.len - 1; i >= 0; i--) {
      if (a.digit[i] < b.digit[i]) return false;
      if (a.digit[i] > b.digit[i]) return true;
    }
    return false;
  }
}

void operator*=(BigInt &a, int b) {
  if (b < 0) {
    a.sign = -a.sign;
    b = -b;
  }
  if (b == 1) return;
  for (int i = 0; i < a.len; i++) a.digit[i] *= b;
  for (int i = 0; i < a.len; i++) {
    if (a.digit[i] >= M) {
      a.digit[i + 1] += a.digit[i] / M;
      if (i + 1 >= a.len) a.len = i + 2;
      a.digit[i] %= M;
    }
  }
}

BigInt product(int i, int j) {
  BigInt res;
  res.digit[0] = 1;
  for (int k = i; k <= j; k++) res *= a[k];
  return res;
}

void update(BigInt &a, BigInt b) {
  if (a < b) a = b;
}

void input() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
}

void solve() {
  bool has_zero = false;
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      has_zero = true;
      break;
    }
  }
  if (!has_zero) ans.sign = -2;
  int i = 0;
  while (i < n && a[i] == 0) i++;
  while (i < n) {
    int j = i + 1;
    while (j < n && a[j] != 0) j++;
    int num_negative = 0;
    for (int k = i; k < j; k++) {
      if (a[k] < 0) num_negative++;
    }
    if (num_negative % 2 == 0)
      update(ans, product(i, j - 1));
    else if (i == j - 1)
      update(ans, product(i, j - 1));
    else {
      int i1 = i;
      while (a[i1] > 0) i1++;
      int j1 = j - 1;
      while (a[j1] > 0) j1--;
      if (i <= j1 - 1) update(ans, product(i, j1 - 1));
      if (i1 + 1 <= j - 1) update(ans, product(i1 + 1, j - 1));
    }
    i = j + 1;
  }
}

void output() {
  if (ans.sign == -1) printf("-");
  printf("%d", ans.digit[ans.len - 1]);
  for (int i = ans.len - 2; i >= 0; i--) printf("%08d", ans.digit[i]);
  printf("\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

/**
 * a may >= n
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

int modpow(int a, int b, int n) {
  int bin[32];
  int tail = 0;
  while (b > 0) {
    bin[tail] = b % 2;
    b /= 2;
    tail++;
  }
  int ans = 1;
  for (int i = tail - 1; i >= 0; i--) {
    ans = ans * ans % n;
    if (bin[i] == 1) ans = ans * a % n;
  }
  return ans;
}

void my_assert(bool cond) {
  while (!cond) printf("1\n");
}

int legendre(int a, int n) {
  if (a % n == 0)
    return 0;
  else {
    int b = modpow(a, (n - 1) / 2, n);
    if (b == 1)
      return 1;
    else {
      assert(b == n - 1);
      return -1;
    }
  }
}

int gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int g = gcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - a / b * y;
  return g;
}

int modinv(int a, int n) {
  int x, y;
  gcd(a, n, x, y);
  x %= n;
  return (x + n) % n;
}

void solve(int a, int n) {
  a %= n;
  if (legendre(a, n) != 1) {
    printf("No root\n");
    return;
  }
  if (n == 2) {
    assert(a == 1);
    printf("%d\n", 1);
    return;
  }
  int a1 = modinv(a, n);
  int q = n - 1, s = 0;
  while (q % 2 == 0) {
    q /= 2;
    s++;
  }
  int w;
  do {
    w = rand() % n;
  } while (legendre(w, n) != -1);
  int v = modpow(w, q, n);
  int x = modpow(a, (q + 1) / 2, n);
  while (true) {
    int res = x * x % n * a1 % n, i = 0;
    while (res != 1) {
      res = res * res % n;
      i++;
    }
    if (i == 0) break;
    int b = v;
    for (int j = 0; j < s - i - 1; ++j) b = b * b % n;
    x = x * b % n;
  }
  int x1 = (n - x) % n;
  my_assert(x * x % n == a && x1 * x1 % n == a);
  printf("%d %d\n", min(x, x1), max(x, x1));
}

int main() {
  int T;
  scanf("%d", &T);
  for (int I = 0; I < T; I++) {
    int a, n;
    scanf("%d %d", &a, &n);
    solve(a, n);
  }
  return 0;
}

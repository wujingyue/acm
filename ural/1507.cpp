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

const int max_n = 64;

typedef int Matrix[max_n][max_n];

Matrix a, c, d;
int n;

void input() {
  scanf("%d", &n);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      int k;
      scanf("%d", &k);
      a[x][y] = (k == 0 ? 0 : 1);
    }
  }
}

void multiply(Matrix c, Matrix a, Matrix b) {
  Matrix d;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      d[x][y] = 0;
      for (int z = 0; z < n; z++) {
        if (a[x][z] && b[z][y]) {
          d[x][y] = 1;
          break;
        }
      }
    }
  }
  memcpy(c, d, sizeof(Matrix));
}

void init_matrix(Matrix a) {
  memset(a, 0, sizeof a);
  for (int x = 0; x < n; x++) a[x][x] = 1;
}

void solve() {
  init_matrix(c);
  int k = n * (n - 1);
  int tail = 0;
  int bin[100];
  while (k > 0) {
    bin[tail] = k % 2;
    tail++;
    k /= 2;
  }
  for (int i = tail - 1; i >= 0; i--) {
    multiply(c, c, c);
    if (bin[i] == 1) multiply(c, c, a);
  }
  // c == a ^ (n(n - 1))
  memcpy(d, c, sizeof(Matrix));
  for (int i = n * (n - 1) + 1; i <= n * (n + 1); i++) {
    multiply(c, c, a);
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) d[x][y] |= c[x][y];
    }
  }
}

void output() {
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (d[x][y] == 0) {
        printf("No\n");
        return;
      }
    }
  }
  printf("Yes\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

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

const int M = 1000000009;

typedef int Vector[100];
typedef int Matrix[100][100];

Matrix a, c;
Vector b;
int n;
int bin[100];
bool prime[1000];

void init() {
  prime[0] = prime[1] = false;
  for (int i = 2; i < 1000; i++) {
    int c;
    for (c = 2; c < i; c++) {
      if (i % c == 0) break;
    }
    prime[i] = (c >= i);
    /*
    if (prime[i])
            cerr << i << endl;
    */
  }
}

void input() { cin >> n; }

void multiply(Matrix c, Matrix a, Matrix b) {
  Matrix d;
  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      d[x][y] = 0;
      for (int z = 0; z < 100; z++)
        d[x][y] = (d[x][y] + (long long)a[x][z] * b[z][y] % M) % M;
    }
  }
  memcpy(c, d, sizeof(Matrix));
}

void apply(Vector c, Matrix a, Vector b) {
  Vector d;
  for (int x = 0; x < 100; x++) {
    d[x] = 0;
    for (int z = 0; z < 100; z++)
      d[x] = (d[x] + (long long)a[x][z] * b[z] % M) % M;
  }
  memcpy(c, d, sizeof(Vector));
}

void solve() {
  memset(a, 0, sizeof a);
  for (int i = 10; i < 100; i++) {
    for (int d = 0; d < 10; d++) {
      if (prime[i * 10 + d]) a[(i * 10 + d) % 100][i] = 1;
    }
  }
  memset(b, 0, sizeof b);
  for (int i = 100; i < 1000; i++) {
    if (prime[i]) b[i % 100]++;
  }
  int k = n - 3;
  int tail = 0;
  while (k > 0) {
    bin[tail] = k % 2;
    k /= 2;
    tail++;
  }
  memset(c, 0, sizeof c);
  for (int x = 0; x < 100; x++) c[x][x] = 1;
  for (int i = tail - 1; i >= 0; i--) {
    multiply(c, c, c);
    if (bin[i] == 1) multiply(c, c, a);
  }
  apply(b, c, b);
}

void output() {
  int ans = 0;
  for (int i = 0; i < 100; i++) ans = (ans + b[i]) % M;
  cout << ans << endl;
}

int main() {
  init();
  input();
  solve();
  output();
  return 0;
}

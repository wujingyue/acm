#include <algorithm>
#include <cassert>
#include <cctype>
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

const char LU = (char)218, RU = (char)191, LB = (char)192, RB = (char)217,
           H = (char)196, V = (char)179;

struct Square {
  int x, y, k;
};

const int MAX_M = 64, MAX_N = 64;

int m, n;
char a[MAX_M][MAX_N];

int main() {
  m = 20;
  n = 50;
  memset(a, '.', sizeof a);
  int ns;
  scanf("%d", &ns);
  for (int i = 0; i < ns; i++) {
    int x1, y1, x2, y2, k;
    scanf("%d %d %d", &y1, &x1, &k);
    x2 = x1 + k - 1;
    y2 = y1 + k - 1;
    a[x1][y1] = LU;
    a[x1][y2] = RU;
    a[x2][y1] = LB;
    a[x2][y2] = RB;
    for (int x = x1 + 1; x < x2; x++) {
      a[x][y1] = V;
      a[x][y2] = V;
    }
    for (int y = y1 + 1; y < y2; y++) {
      a[x1][y] = H;
      a[x2][y] = H;
    }
  }
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) printf("%c", a[x][y]);
    printf("\n");
  }
  return 0;
}

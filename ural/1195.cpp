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
typedef int Table[3][3];

const Real o = 1e-8;
const int max_s = 19683;

int c[max_s][2];
int u;
int ans;

void input() {
  u = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      char ch;
      scanf(" %c ", &ch);
      int k;
      if (ch == 'X')
        k = 0;
      else if (ch == 'O')
        k = 1;
      else
        k = 2;
      u = u * 3 + k;
    }
  }
}

void num2arr(int s, Table a) {
  for (int x = 2; x >= 0; x--) {
    for (int y = 2; y >= 0; y--) {
      a[x][y] = s % 3;
      s /= 3;
    }
  }
}

int arr2num(Table a) {
  int res = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) res = res * 3 + a[x][y];
  }
  return res;
}

int get_winner(Table a) {
  for (int x = 0; x < 3; x++) {
    if (a[x][0] < 2 && a[x][0] == a[x][1] && a[x][1] == a[x][2]) return a[x][0];
  }
  for (int y = 0; y < 3; y++) {
    if (a[0][y] < 2 && a[0][y] == a[1][y] && a[1][y] == a[2][y]) return a[0][y];
  }
  if (a[0][0] < 2 && a[0][0] == a[1][1] && a[1][1] == a[2][2]) return a[0][0];
  if (a[0][2] < 2 && a[0][2] == a[1][1] && a[1][1] == a[2][0]) return a[0][2];
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (a[x][y] == 2) return -1;
    }
  }
  return 2;
}

int get_c(int s, int p) {
  if (c[s][p] != -1) return c[s][p];
  Table a;
  num2arr(s, a);
  int res = get_winner(a);
  if (res >= 0) {
    c[s][p] = res;
    return res;
  }
  bool draw = false;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (a[x][y] == 2) {
        a[x][y] = p;
        int s1 = arr2num(a);
        res = get_c(s1, 1 - p);
        if (res == p) {
          c[s][p] = p;
          return p;
        }
        if (res == 2) draw = true;
        a[x][y] = 2;
      }
    }
  }
  if (draw)
    c[s][p] = 2;
  else
    c[s][p] = 1 - p;
  return c[s][p];
}

void solve() {
  memset(c, -1, sizeof c);
  ans = get_c(u, 0);
}

void output() {
  if (ans == 0)
    printf("Crosses win\n");
  else if (ans == 1)
    printf("Ouths win\n");
  else
    printf("Draw\n");
}

int main() {
  input();
  solve();
  output();
  return 0;
}

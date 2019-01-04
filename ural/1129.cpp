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

const int max_n = 128;

int n;
bool a[max_n][max_n];
int dir[max_n][max_n];

void my_assert(bool cond) { assert(cond); }

void input() {
  cin >> n;
  memset(a, 0, sizeof a);
  for (int x = 0; x < n; x++) {
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
      int y;
      cin >> y;
      y--;
      a[x][y] = a[y][x] = true;
    }
  }
}

bool find_path(int x, int color) {
  for (int y = 0; y < n; y++) {
    if (a[x][y] && dir[x][y] == 0) {
      dir[x][y] = color;
      dir[y][x] = -color;
      find_path(y, color);
      return true;
    }
  }
  return false;
}

void solve() {
  memset(dir, 0, sizeof dir);
  int color = 1;
  for (int x = 0; x < n; x++) {
    while (find_path(x, color)) color = -color;
  }
}

void output() {
  for (int x = 0; x < n; x++) {
    bool first = true;
    for (int y = 0; y < n; y++) {
      if (a[x][y]) {
        if (first)
          first = false;
        else
          cout << ' ';
        if (dir[x][y] == 1)
          cout << 'G';
        else
          cout << 'Y';
      }
    }
    cout << endl;
  }
#if 1
  for (int x = 0; x < n; x++) {
    int in_d = 0, out_d = 0;
    for (int y = 0; y < n; y++) {
      if (a[x][y]) {
        my_assert(dir[x][y] != 0 && dir[y][x] != 0);
        my_assert(dir[x][y] != dir[y][x]);
        if (dir[x][y] == 1)
          out_d++;
        else
          in_d++;
      }
    }
    my_assert(abs(in_d - out_d) <= 1);
  }
#endif
}

int main() {
  input();
  solve();
  output();
  return 0;
}

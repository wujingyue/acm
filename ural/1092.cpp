/**
 * forgot to increase y in exchange
 * could be detected by some larger cases
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

const int MAX_N = 64;

int n;
char a[MAX_N][MAX_N];

void input() {
  scanf("%d", &n);
  n = n * 2 + 1;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      char ch;
      for (ch = getchar(); ch != '+' && ch != '-'; ch = getchar())
        ;
      a[x][y] = ch;
    }
  }
}

void do_trans(const vector<int> &trans) {
  for (int x = 0; x < n; x++) {
    int y = trans[x];
    if (a[x][y] == '+')
      a[x][y] = '-';
    else
      a[x][y] = '+';
    if (x > 0) printf(" ");
    printf("%d", y + 1);
  }
  printf("\n");
}

void exchange(int xx, int yy, int m) {
  int y = 0;
  vector<int> trans;
  for (int x = 0; x < m - 1; x++) {
    if (x == xx)
      trans.push_back(m - 1);
    else {
      while (y == yy) y++;
      assert(y < m);
      trans.push_back(y);
      // forgot y++ at first
      y++;
    }
  }
  trans.push_back(yy);
  for (int x = m; x < n; x++) trans.push_back(x);
  do_trans(trans);
}

void reduce(int m) {
  vector<int> bot, rig;
  for (int x = 0; x < m - 1; x++) {
    if (a[x][m - 1] == '+') rig.push_back(x);
  }
  for (int y = 0; y < m - 1; y++) {
    if (a[m - 1][y] == '+') bot.push_back(y);
  }
  size_t i = 0, j = 0;
  while (i < bot.size() && j < rig.size()) {
    int x = rig[j], y = bot[i];
    exchange(x, y, m);
    i++;
    j++;
  }
  while (i + 1 < bot.size()) {
    exchange(0, bot[i], m);
    exchange(0, bot[i + 1], m);
    i += 2;
  }
  if (i < bot.size()) {
    exchange(0, bot[i], m);
    exchange(0, m - 2, m);
  }
  while (j + 1 < rig.size()) {
    exchange(rig[j], 0, m);
    exchange(rig[j + 1], 0, m);
    j += 2;
  }
  if (j < rig.size()) {
    exchange(rig[j], m - 2, m);
  }
}

void solve() {
  printf("There is solution:\n");
  for (int m = n; m >= 2; m--) {
    reduce(m);
  }
  int num;
  num = 0;
  for (int x = 0; x < n; x++) {
    if (a[x][x] == '+') num++;
  }
  if (num > n / 2) {
    vector<int> trans;
    for (int x = 0; x < n; x++) trans.push_back(x);
    do_trans(trans);
  }
  num = 0;
  for (int x = 0; x < n; x++) {
    if (a[x][(x + n - 1) % n] == '+') num++;
  }
  if (num > n / 2) {
    vector<int> trans;
    for (int x = 0; x < n; x++) trans.push_back((x + n - 1) % n);
    do_trans(trans);
  }
}

void output() {
  int num = 0;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (a[x][y] == '+') num++;
    }
  }
  if (num >= n) {
    while (true)
      ;
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

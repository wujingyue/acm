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

const int max_n = 1024;

vector<int> a[max_n];
int d[max_n], c[max_n];
int n;

void search(int x) {
  if (a[x].empty()) return;
  if (d[x] % 2 == 0)
    c[x] = -1;
  else
    c[x] = 1;
  for (vector<int>::iterator it = a[x].begin(); it != a[x].end(); ++it) {
    int y = *it;
    d[y] = d[x] + 1;
    search(y);
    if (d[x] % 2 == 0)
      c[x] = max(c[x], c[y]);
    else
      c[x] = min(c[x], c[y]);
  }
}

void input() {
  scanf("%d", &n);
  for (int x = 0; x < n; x++) a[x].clear();
  for (int x = 1; x < n; x++) {
    char ch;
    int y;
    scanf(" %c %d", &ch, &y);
    y--;
    a[y].push_back(x);
    // fprintf(stderr, "%c\n", ch);
    if (ch == 'L') scanf("%d", &c[x]);
  }
}

void solve() {
  d[0] = 0;
  search(0);
}

void output() {
  if (c[0] == 1) printf("+");
  printf("%d\n", c[0]);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

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

pair<int, int> a[max_n];
int c[max_n], f[max_n];
bool del[max_n];
int n;

bool by_length(const pair<int, int> &a, const pair<int, int> &b) {
  return a.second - a.first < b.second - b.first;
}

void input() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
    if (a[i].first > a[i].second) swap(a[i].first, a[i].second);
  }
}

void solve() {
  sort(a, a + n, by_length);
  for (int i = 0; i < n; i++) {
    del[i] = false;
    for (int j = 0; j < i; j++) {
      if (a[j].first >= a[i].first && a[j].second <= a[i].second) {
        del[i] = true;
        break;
      }
    }
  }
  int n1 = 0;
  for (int i = 0; i < n; i++) {
    if (!del[i]) {
      a[n1] = a[i];
      n1++;
    }
  }
  n = n1;
  sort(a, a + n);
  c[0] = 1;
  f[0] = -1;
  for (int i = 1; i < n; i++) {
    c[i] = 1;
    f[i] = -1;
    for (int j = 0; j < i; j++) {
      if (a[j].second <= a[i].first && c[j] + 1 > c[i]) {
        c[i] = c[j] + 1;
        f[i] = j;
      }
    }
  }
}

void print(int i) {
  if (i == -1) return;
  print(f[i]);
  cout << a[i].first << ' ' << a[i].second << endl;
}

void output() {
  cout << c[n - 1] << endl;
  print(n - 1);
}

int main() {
  input();
  solve();
  output();
  return 0;
}

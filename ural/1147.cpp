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
const int max_r = max_n * 2;
const int max_t = max_r * 2;
const int max_c = 4096;

struct Rect {
  int x1, y1, x2, y2, color;
};

int R, C, n;
Rect r[max_n];
int low[max_t], high[max_t], mid[max_t], color[max_t];
vector<int> X, Y;
int ans[max_c];

void input() {
  cin >> R >> C >> n;
  for (int i = 0; i < n; i++)
    cin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2 >> r[i].color;
}

void create_tree(int i, int l, int h) {
  low[i] = l;
  high[i] = h;
  mid[i] = (l + h) / 2;
  if (h - l > 1) {
    create_tree(i * 2 + 1, l, mid[i]);
    create_tree(i * 2 + 2, mid[i], h);
  }
}

void init_tree() {
  for (int i = 0; i < max_t; i++) color[i] = 1;
}

void insert_tree(int i, int l, int h, int c) {
  if (l <= low[i] && h >= high[i]) {
    color[i] = c;
    return;
  }
  if (color[i] == c) return;
  if (color[i] >= 0) {
    color[i * 2 + 1] = color[i];
    color[i * 2 + 2] = color[i];
    color[i] = -1;
  }
  if (l < mid[i]) insert_tree(i * 2 + 1, l, h, c);
  if (h > mid[i]) insert_tree(i * 2 + 2, l, h, c);
}

void summary_tree(int i, int height) {
  if (color[i] >= 0) {
    ans[color[i]] += (X[high[i]] - X[low[i]]) * height;
    return;
  }
  summary_tree(i * 2 + 1, height);
  summary_tree(i * 2 + 2, height);
}

void solve() {
  X.clear();
  Y.clear();
  X.push_back(0);
  X.push_back(R);
  Y.push_back(0);
  Y.push_back(C);
  for (int i = 0; i < n; i++) {
    X.push_back(r[i].x1);
    X.push_back(r[i].x2);
    Y.push_back(r[i].y1);
    Y.push_back(r[i].y2);
  }
  sort(X.begin(), X.end());
  X.resize(unique(X.begin(), X.end()) - X.begin());
  sort(Y.begin(), Y.end());
  Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
  for (int i = 0; i < n; i++) {
    r[i].x1 = lower_bound(X.begin(), X.end(), r[i].x1) - X.begin();
    r[i].x2 = lower_bound(X.begin(), X.end(), r[i].x2) - X.begin();
    r[i].y1 = lower_bound(Y.begin(), Y.end(), r[i].y1) - Y.begin();
    r[i].y2 = lower_bound(Y.begin(), Y.end(), r[i].y2) - Y.begin();
  }
  R = X.size() - 1;
  C = Y.size() - 1;

  memset(ans, 0, sizeof ans);
  create_tree(0, 0, R);
  for (int y = 0; y < C; y++) {
    init_tree();
    for (int i = 0; i < n; i++) {
      if (r[i].y1 <= y && r[i].y2 >= y + 1)
        insert_tree(0, r[i].x1, r[i].x2, r[i].color);
    }
    summary_tree(0, Y[y + 1] - Y[y]);
  }
}

void output() {
  for (int i = 1; i < max_c; i++) {
    if (ans[i] > 0) printf("%d %d\n", i, ans[i]);
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

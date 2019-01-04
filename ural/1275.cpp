/**
 * the minimum step
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

const int max_n = 1024;

int a[max_n], b[max_n];
bool visit[max_n];
int n, k, f;
bool ans;
vector<int> delta;

void input() {
  scanf("%d %d %d", &n, &k, &f);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
}

bool search(int u) {
  int x = u;
  int len = 0;
  while (!visit[x]) {
    visit[x] = true;
    len++;
    x = (x + k) % n;
  }
  b[u] = 0;
  x = u;
  do {
    int y = (x + k) % n;
    b[y] = f - a[x] - b[x];
    x = y;
  } while ((x + k) % n != u);
  int y = (u - k + n) % n;
  int new_b = f - a[y] - b[y];
  if (len % 2 == 0) {
    if (new_b != b[u]) return false;
    delta.clear();
    x = u;
    int sign = -1;
    do {
      delta.push_back(b[x] * sign);
      sign = -sign;
      x = (x + k) % n;
    } while (x != u);
    sort(delta.begin(), delta.end());
    assert(delta.size() % 2 == 0);
    b[u] += delta[delta.size() / 2 - 1];
    x = u;
    do {
      int y = (x + k) % n;
      b[y] = f - a[x] - b[x];
      x = y;
    } while ((x + k) % n != u);
    return true;
  }
  if ((b[u] + new_b) % 2 != 0) return false;
  b[u] = (b[u] + new_b) / 2;
  x = (u + k) % n;
  while (x != u) {
    int y = (x - k + n) % n;
    b[x] = f - a[y] - b[y];
    x = (x + k) % n;
  }
  return true;
}

void solve() {
  memset(visit, 0, sizeof visit);
  for (int i = 0; i < n; i++) {
    if (!visit[i]) {
      bool ret = search(i);
      if (!ret) {
        ans = false;
        return;
      }
    }
  }
  ans = true;
}

void output() {
  if (!ans)
    printf("-1\n");
  else {
    int num = 0;
    for (int i = 0; i < n; i++) num += abs(b[i]);
    printf("%d\n", num);
    for (int i = 0; i < n; i++) {
      if (b[i] > 0) {
        for (int t = 0; t < b[i]; ++t)
          printf("%d %d +\n", i + 1, (i - k + n) % n + 1);
      }
    }
    for (int i = 0; i < n; i++) {
      if (b[i] < 0) {
        for (int t = 0; t > b[i]; --t)
          printf("%d %d -\n", i + 1, (i - k + n) % n + 1);
      }
    }
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

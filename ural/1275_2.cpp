/**
 * the minimum step
 * if the length of the cycle is even, there are multiple solutions leading to
 * different number of services the function from b0 to the number of services
 * is concave therefore, we can perform a tenary search to find the lowest point
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
const int oo = 0x7fffffff;

int a[max_n], b[max_n];
bool visit[max_n];
int n, k, f;
bool ans;
vector<int> delta;

void input() {
  scanf("%d %d %d", &n, &k, &f);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
}

void propagate(int u, int s) {
  b[u] = s;
  for (int x = (u + k) % n; x != u; x = (x + k) % n) {
    int y = (x - k + n) % n;
    b[x] = f - a[y] - b[y];
  }
}

int get_sum(int u, int s) {
  propagate(u, s);
  int x = u;
  int res = 0;
  do {
    res += abs(b[x]);
    x = (x + k) % n;
  } while (x != u);
  return res;
}

bool search(int u) {
  int x = u;
  int len = 0;
  while (!visit[x]) {
    visit[x] = true;
    len++;
    x = (x + k) % n;
  }
  propagate(u, 0);
  int y = (u - k + n) % n;
  int new_b = f - a[y] - b[y];
  if (len % 2 == 0) {
    if (new_b != b[u]) return false;
    int low = -30000, high = 30000;
    while (high - low > 2) {
      int m1 = low + (high - low) / 3, m2 = low + (high - low) / 3 * 2;
      if (get_sum(u, m1) < get_sum(u, m2))
        high = m2;
      else
        low = m1;
    }
    int min_sum = oo, mi = -1;
    for (int i = low; i <= high; ++i) {
      int tmp = get_sum(u, i);
      if (tmp < min_sum) {
        min_sum = tmp;
        mi = i;
      }
    }
    propagate(u, mi);
    return true;
  }
  if ((b[u] + new_b) % 2 != 0) return false;
  propagate(u, (b[u] + new_b) / 2);
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

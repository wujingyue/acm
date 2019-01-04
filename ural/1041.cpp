/**
 * use long long
 * remember to divide the vector by its greatest common divisor
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
const int MAX_M = 2048;

int m, n;
long long a[MAX_M][MAX_N], b[MAX_M][MAX_N];
pair<int, int> r[MAX_M];
vector<pair<int, int> > chosen;

void input() {
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) scanf("%lld", &a[i][j]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &r[i].first);
    r[i].second = i;
  }
  sort(r, r + m);
  memcpy(b, a, sizeof a);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) a[i][j] = b[r[i].second][j];
  }
}

long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

void reduce(int i, int ii, int j) {
  if (a[i][j] == 0) return;
  long long ki = a[i][j], kii = a[ii][j];
  long long g = 0;
  for (int k = 0; k < n; k++) {
    a[i][k] = a[i][k] * kii - a[ii][k] * ki;
    g = gcd(g, a[i][k]);
  }
  if (g == 0) return;
  for (int k = 0; k < n; k++) a[i][k] /= g;
}

void solve() {
  chosen.clear();
  for (int i = 0; i < m; i++) {
    for (size_t k = 0; k < chosen.size(); k++)
      reduce(i, chosen[k].first, chosen[k].second);
    int mj = -1;
    for (int j = 0; j < n; j++) {
      if (a[i][j] != 0) {
        mj = j;
        break;
      }
    }
    if (mj >= 0) chosen.push_back(make_pair(i, mj));
  }
}

void output() {
#if 0
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			fprintf(stderr, "%Lf ", a[i][j]);
		fprintf(stderr, ":%d\n", r[i].first);
	}
#endif
  if ((int)chosen.size() < n)
    printf("0\n");
  else {
    int ans = 0;
    for (int k = 0; k < n; k++) ans += r[chosen[k].first].first;
    printf("%d\n", ans);
    vector<int> ids;
    for (int k = 0; k < n; k++) ids.push_back(r[chosen[k].first].second + 1);
    sort(ids.begin(), ids.end());
    for (int k = 0; k < n; k++) printf("%d\n", ids[k]);
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}

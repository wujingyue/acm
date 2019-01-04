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

const int MAX_N = 256 * 1024;

long double a[MAX_N], ans[MAX_N];

int main() {
  int n = 0;
  while (scanf("%Lf", &a[n]) != EOF) {
    n++;
  }
  for (int i = 0; i < n; i++) {
    ans[n - 1 - i] = sqrt(a[i]);
  }
  for (int i = 0; i < n; i++) {
    printf("%.4Lf\n", ans[i]);
  }
  return 0;
}

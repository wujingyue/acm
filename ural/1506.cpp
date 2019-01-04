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

int a[max_n];

int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  int len = (n + k - 1) / k;
  for (int i = 0; i < len; i++) {
    for (int j = i; j < n; j += len) printf("%4d", a[j]);
    printf("\n");
  }
  return 0;
}

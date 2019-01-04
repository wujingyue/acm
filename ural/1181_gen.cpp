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

typedef long double Real;

const Real o = 1e-8;
const Real pi = acos(-1.0);

const int n = 1000;

int a[n];

int main() {
  srand(time(NULL));
  printf("%d\n", n);
  do {
    a[0] = rand() % 3;
    for (int i = 1; i < n; i++) {
      do {
        a[i] = rand() % 3;
      } while (a[i] == a[i - 1]);
    }
    if (a[0] == a[n - 1]) continue;
    int s = 0;
    for (int i = 0; i < n; i++) {
      s |= (1 << a[i]);
    }
    if (s != 7) continue;
    break;
  } while (true);
  for (int i = 0; i < n; i++) {
    printf("%c", (a[i] == 0 ? 'R' : (a[i] == 1 ? 'G' : 'B')));
  }
  printf("\n");
  return 0;
}

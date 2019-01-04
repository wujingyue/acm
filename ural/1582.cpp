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

int main() {
  long double k1, k2, k3;
  scanf("%Lf %Lf %Lf", &k1, &k2, &k3);
  k1 = 1 / k1;
  k2 = 1 / k2;
  k3 = 1 / k3;
  printf("%.0Lf\n", 1000 / (k1 + k2 + k3));
  return 0;
}

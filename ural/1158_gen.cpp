#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int n = 5, m = 50, p = 10;

int main() {
  srand(time(NULL));
  printf("%d %d %d\n", n, m, p);
  for (int i = 0; i < n; i++) printf("%c", 'A' + i);
  printf("\n");
  for (int i = 0; i < p; i++) {
    int max_l = min(m, 10);
    int len = rand() % max_l + 1;
    for (int j = 0; j < len; j++) printf("%c", 'A' + rand() % n);
    printf("\n");
  }
  return 0;
}

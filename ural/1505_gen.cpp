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

const int n = 10000;

int main() {
  FILE *fout = fopen("1505_0.in", "w");
  fprintf(fout, "%d\n", n);
  for (int i = 1; i < n; i++) {
    fprintf(fout, "%d %d %d %d.\n", i + 1, 1, 1, 1000000);
  }
  fprintf(fout, ".\n");
  fclose(fout);
  return 0;
}

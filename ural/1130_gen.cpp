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
  FILE *fout = fopen("1130_0.in", "w");
  fprintf(fout, "%d\n", n);
  fprintf(fout, "1000\n");
  for (int i = 0; i < n; i++) {
    int x = rand() % 200 - 100, y = rand() % 200 - 100;
    fprintf(fout, "%d %d\n", x, y);
  }
  fclose(fout);
  return 0;
}

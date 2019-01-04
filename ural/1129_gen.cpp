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

const int n = 100;

bool a[n][n];

int main() {
  FILE *fout = fopen("1129_0.in", "w");
  fprintf(fout, "%d\n", n);
  memset(a, 0, sizeof a);
  for (int x = 0; x < n; x++) {
    for (int y = x + 1; y < n; y++) {
      if (rand() % 2 == 0) {
        a[x][y] = true;
        a[y][x] = true;
      }
    }
  }
  for (int x = 0; x < n; x++) {
    int d = 0;
    for (int y = 0; y < n; y++) {
      if (a[x][y]) d++;
    }
    fprintf(fout, "%d", d);
    for (int y = 0; y < n; y++) {
      if (a[x][y]) fprintf(fout, " %d", y + 1);
    }
    fprintf(fout, "\n");
  }
  fclose(fout);
  return 0;
}

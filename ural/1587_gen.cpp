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

const int n = 50000;

int main() {
  FILE *fout = fopen("1587_0.in", "w");
  fprintf(fout, "%d\n", n);
  for (int i = 0; i < n; i++) fprintf(fout, "%d ", rand() % 3 + 1);
  fprintf(fout, "\n");
  fclose(fout);
  return 0;
}

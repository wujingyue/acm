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

const int m = 20, n = 20;
vector<char> chs;

int main() {
  srand(time(NULL));
  FILE *fout = fopen("1584_0.in", "w");
  fprintf(fout, "%d %d\n", m, n);
  chs.clear();
  for (int x = 0; x < m / 2; x++) {
    for (int y = 0; y < n / 2; y++) {
      char ch = 'a' + rand() % 26;
      for (int i = 0; i < 4; i++) chs.push_back(ch);
    }
  }
  assert(chs.size() == m * n);
  random_shuffle(chs.begin(), chs.end());
  size_t i = 0;
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) {
      fprintf(fout, "%c", chs[i]);
      i++;
    }
    fprintf(fout, "\n");
  }
  fclose(fout);
  return 0;
}

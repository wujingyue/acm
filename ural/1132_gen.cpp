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

const int T = 100000;

bool is_prime(int a) {
  for (int c = 2; c <= min(a - 1, (int)(sqrt((double)a) + 0.5)); c++) {
    if (a % c == 0) return false;
  }
  return true;
}

int main() {
  vector<int> prime;
  prime.clear();
  for (int i = 2; i <= 32767; i++) {
    if (is_prime(i)) prime.push_back(i);
  }
  FILE *fout = fopen("1132_0.in", "w");
  fprintf(fout, "%d\n", T);
  for (int I = 0; I < T; I++) {
    int n = prime[rand() % prime.size()];
    int a = rand() % (n - 1) + 1;
    fprintf(fout, "%d %d\n", a, n);
  }
  fclose(fout);
  return 0;
}

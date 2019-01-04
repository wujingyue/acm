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

vector<int> a;

int main() {
  int m;
  scanf("%d", &m);
  a.clear();
  a.push_back(-1);
  int p = 0;
  for (int k = 1; k * 2 <= m; k *= 2) {
    a.push_back(p);
    p++;
  }
  // cerr << p << endl;
  for (int i = p - 1; i >= 0; i--) {
    if ((m & (1 << i)) > 0) a.push_back(i);
  }
  for (int i = a.size() - 1; i >= 0; i--) {
    if (a[i] == -1)
      printf("BELL&RET\n");
    else
      printf("CALL %d\n", a.size() - 1 - a[i]);
  }
  return 0;
}

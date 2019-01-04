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

const string word[] = {"out", "output", "puton", "in", "input", "one"};
const int MAX_N = 10000001;

char a[MAX_N];
int n;
bool c[16];

void input() { cin >> a; }

int match(int i, int j) {
  if (i + 1 < (int)word[j].size()) return -2;
  for (int k = (int)word[j].size() - 1; k >= 0; k--) {
    if (word[j][k] != a[i]) return -2;
    i--;
  }
  return i;
}

void solve() {
  n = strlen(a);
  for (int i = 0; i < n; i++) {
    // cerr << "i = " << i << endl;
    bool new_c = false;
    for (int j = 0; j < 6; j++) {
      int i1 = match(i, j);
      /*
      if (i1 != -2)
              cerr << i1 << endl;
      */
      if (i1 == -1)
        new_c = true;
      else if (i1 >= 0)
        new_c |= c[i - i1];
    }
    c[6] = c[5];
    c[5] = c[4];
    c[4] = c[3];
    c[3] = c[2];
    c[2] = c[1];
    c[1] = new_c;
  }
}

void output() {
  if (c[1])
    printf("YES\n");
  else
    printf("NO\n");
}

int main() {
  int T, I;
  scanf("%d", &T);
  for (I = 0; I < T; I++) {
    input();
    solve();
    output();
  }
  return 0;
}

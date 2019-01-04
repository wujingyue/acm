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

long long S;
vector<long long> ans;
long long p10[20];

void input() { scanf("%lld", &S); }

int len(long long a) {
  int res = 0;
  while (a > 0) {
    res++;
    a /= 10;
  }
  return res;
}

void solve() {
  for (int i = 0; i <= 9; i++) {
    for (int digit = 0; digit <= 9; digit++) {
      long long low, high;
      low = 0;
      high = 1000000000;
      bool found = false;
      while (low <= high) {
        long long a = (low + high) / 2;
        if (digit == 0 && i >= len(a)) {
          low = a + 1;
          continue;
        }
        long long res =
            a % p10[i] + a / p10[i] * p10[i + 1] + digit * p10[i] + a;
        if (res == S) {
          low = high = a;
          found = true;
          break;
        } else if (res < S) {
          low = a + 1;
        } else {
          high = a - 1;
        }
      }
      if (found) {
        assert(low == high);
        // cerr << low << ' ' << i << ' ' << digit << endl;
        ans.push_back(S - low);
      }
    }
  }
}

void output() {
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  printf("%u\n", ans.size());
  for (size_t i = 0; i < ans.size(); ++i) {
    long long b = ans[i], a = S - b;
    printf("%lld + ", b);
    for (int k = 0; k < len(b) - len(a) - 1; ++k) printf("0");
    if (a > 0) printf("%lld", a);
    printf(" = %lld\n", S);
  }
}

void init() {
  p10[0] = 1;
  for (int i = 1; i < 15; i++) p10[i] = p10[i - 1] * 10;
}

int main() {
  init();
  input();
  solve();
  output();
  return 0;
}

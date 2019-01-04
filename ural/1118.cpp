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

const int max_r = 1048576;
const int max_p = 32;
const int max_prime = 100000;

int c[max_r];
vector<int> prime;
bool is_prime[max_r];
vector<int> power[max_prime], sum_power[max_prime];

void init() {
  memset(is_prime, true, sizeof is_prime);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i < max_r; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j < max_r; j += i) is_prime[j] = false;
    }
  }
  prime.clear();
  for (int i = 2; i < max_r; i++) {
    if (is_prime[i]) prime.push_back(i);
  }
  // cerr << prime.size() << endl;
  for (size_t i = 0; i < prime.size(); i++) {
    power[i].push_back(1);
    sum_power[i].push_back(1);
    int p = 1;
    for (int j = 1; j < max_p; j++) {
      /*
      if (p * prime[i] < max_r)
      if (p * prime[i] <= max_r - 1)
      if (p <= (max_r - 1) / prime[i])
      */
      if (p > (max_r - 1) / prime[i]) break;
      p *= prime[i];
      power[i].push_back(power[i].back() * prime[i]);
      sum_power[i].push_back(sum_power[i].back() + power[i].back());
    }
  }
  c[1] = 1;
  for (int i = 2; i < max_r; i++) {
    c[i] = -1;
    for (size_t j = 0; j < prime.size() && prime[j] * prime[j] <= i; j++) {
      if (i % prime[j] == 0) {
        int k = i, e = 0;
        while (k % prime[j] == 0) {
          k /= prime[j];
          e++;
        }
        c[i] = c[k] * sum_power[j][e];
        break;
      }
    }
    if (c[i] == -1) c[i] = i + 1;
  }
}

void solve() {
  int i, j;
  cin >> i >> j;
  int mi = i;
  for (int k = i + 1; k <= j; k++) {
    if ((long long)c[mi] * k > (long long)c[k] * mi) mi = k;
  }
  cout << mi << endl;
}

int main() {
  init();
  solve();
  return 0;
}

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

const int N = 131072;

int expire[N];
set<int> avail;
priority_queue<pair<int, int>, vector<pair<int, int> >,
               greater<pair<int, int> > >
    h;

void init() {
  while (!h.empty()) h.pop();
  avail.clear();
  for (int x = 0; x < N; x++) avail.insert(x);
  memset(expire, -1, sizeof expire);
}

void solve() {
  int t;
  while (cin >> t) {
    while (!h.empty() && h.top().first <= t) {
      if (expire[h.top().second] == h.top().first) {
        avail.insert(h.top().second);
        expire[h.top().second] = -1;
      }
      h.pop();
    }
    char op;
    cin >> op;
    if (op == '+') {
      int x = *avail.begin();
      printf("%d\n", x + 1);
      expire[x] = t + 600;
      h.push(make_pair(t + 600, x));
      avail.erase(avail.begin());
    } else {
      assert(op == '.');
      int x;
      cin >> x;
      x--;
      if (expire[x] == -1)
        printf("-\n");
      else {
        printf("+\n");
        expire[x] = t + 600;
        h.push(make_pair(t + 600, x));
      }
    }
  }
}

int main() {
  init();
  solve();
  return 0;
}

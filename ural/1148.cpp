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

const int max_n = 32768;
const int max_m = 71;
const int max_h = 61;
const long long oo = 0x7fffffffffffffffLL;
const int max_t = 310000;
const int max_lls = 20000;

struct Record {
  char i;
  char j;
  short k;
  int c;
};
int compare_record(const void *pa, const void *pb) {
  const Record *a = (const Record *)pa;
  const Record *b = (const Record *)pb;
  if (a->i != b->i) return a->i - b->i;
  if (a->j != b->j) return a->j - b->j;
  if (a->k != b->k) return a->k - b->k;
  return 0;
}

long long lls[max_lls];

int n, m, h;
long long idx;
unsigned int visited[max_m][max_n / 32];
int head, tail;
Record q[max_t];
int n_ll;

void my_assert(bool cond) {
  while (!cond)
    ;
}

/* i = m, j = h, k = n */

int Lower_Bound(int i, int j, int k) {
  int low = 0, high = tail - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (q[mid].i == i && q[mid].j == j && q[mid].k == k) return mid;
    if (i < q[mid].i ||
        (i == q[mid].i && (j < q[mid].j || (j == q[mid].j && k < q[mid].k))))
      high = mid - 1;
    else
      low = mid + 1;
  }
  my_assert(false);
  return -1;
}

long long get_c(int c) {
  if (c >= 0)
    return c;
  else
    return lls[-c];
}

void set_c(int &c, long long res) {
  if (res <= 0x7fffffff)
    c = res;
  else {
    my_assert(n_ll < max_lls);
    lls[n_ll] = res;
    c = -n_ll;
    n_ll++;
  }
}

long long work(int i, int j, int k) {
  if (i <= 0) return 0;
  if (i > k) return 0;
  int p = Lower_Bound(i, j, k);
  my_assert(p >= 0 && p < tail);
  my_assert(q[p].i == i && q[p].j == j && q[p].k == k);
#if 0
	if (p == tail)
		return 0;
	if (p.i != i || p.j != j || p.k != k)
		return 0;
#endif
  if (q[p].c != -1) return get_c(q[p].c);
  long long res;
  if (j == 1)
    res = 1;
  else
    res = work(i - 1, j - 1, k - i) + work(i + 1, j - 1, k - i);
  set_c(q[p].c, res);
  return res;
}

inline bool is_visited(int i1, int k1) {
  return (visited[i1][k1 / 32] & (1 << (k1 % 32)));
}

inline void set_visited(int i1, int k1) {
  visited[i1][k1 / 32] |= (1 << (k1 % 32));
}

void init() {
  scanf("%d %d %d", &n, &h, &m);
  memset(q, -1, sizeof q);
  head = 0;
  tail = 1;
  q[0].i = m;
  q[0].j = h;
  q[0].k = n;
  memset(visited, 0, sizeof visited);
  while (head < tail) {
    int i = q[head].i, j = q[head].j, k = q[head].k;
    int i1, j1, k1;
    if (i > 1 && j > 1 && i <= k) {
      i1 = i - 1;
      j1 = j - 1;
      k1 = k - i;
      if (!is_visited(i1, k1)) {
        set_visited(i1, k1);
        my_assert(tail < max_t);
        q[tail].i = i1;
        q[tail].j = j1;
        q[tail].k = k1;
        ++tail;
      }
    }
    if (j > 1 && i <= k) {
      i1 = i + 1;
      j1 = j - 1;
      k1 = k - i;
      if (!is_visited(i1, k1)) {
        set_visited(i1, k1);
        my_assert(tail < max_t);
        q[tail].i = i1;
        q[tail].j = j1;
        q[tail].k = k1;
        ++tail;
      }
    }
    head++;
    if (head < tail && q[head - 1].j != q[head].j)
      memset(visited, 0, sizeof visited);
  }
#if 0
	for (int t = 0; t < tail; ++t)
		cerr << (int)q[t].i << ' ' << (int)q[t].j << ' ' << q[t].k << "\n";
#endif
  qsort(q, tail, sizeof(Record), compare_record);
#if 0
	for (int t = 0; t < tail; ++t) {
		if (q[t].i == 2 && q[t].j == 46 && q[t].k == 32706)
			cerr << "!!!!!!!!!!!!!!!!\n";
	}
#endif
  n_ll = 2;
  printf("%lld\n", work(m, h, n));
#if 0
	cerr << "tail = " << tail << endl;
	cerr << "> INT_MAX: " << n_ll << endl;
#endif
}

bool input() {
  scanf("%lld", &idx);
  return idx != -1;
}

void print(int i, int j, int k, long long idx) {
  my_assert(idx >= 1 && idx <= work(i, j, k));
  if (j == 1) {
    printf("%d\n", i);
    return;
  }
  printf("%d ", i);
  long long left = work(i - 1, j - 1, k - i);
  if (idx <= left)
    print(i - 1, j - 1, k - i, idx);
  else
    print(i + 1, j - 1, k - i, idx - left);
}

void solve() { print(m, h, n, idx); }

void output() {}

int main() {
  init();
  while (input()) {
    solve();
    output();
  }
  return 0;
}

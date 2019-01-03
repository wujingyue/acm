#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

static const int r = 5;
static const int c = 6;
static const int n = r * c;

void GaussianElimination(vector<unsigned>& a) {
  int i = 0;
  for (int j = 0; j < n; ++j) {
    int i2 = i;
    while (i2 < n && (((a[i2] >> j) & 1) == 0)) {
      ++i2;
    }
    if (i2 >= n) {
      continue;
    }
    if (i != i2) {
      swap(a[i], a[i2]);
    }
    assert(((a[i] >> j) & 1) == 1);
    for (i2 = i + 1; i2 < n; ++i2) {
      if (((a[i2] >> j) & 1) == 1) {
        a[i2] ^= a[i];
      }
    }
    ++i;
  }
}

bool SolveXorEquations(vector<unsigned>& a, unsigned& x) {
  GaussianElimination(a);

  x = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (a[i] == 0) {
      continue;
    }
    int j = __builtin_ctz(a[i]);
    if (j == n) {
      return false;
    }

    int xj = (a[i] >> n) ^ (__builtin_popcount(a[i] & x) % 2);
    x |= xj * (1 << j);
  }
  return true;
}

int main() {
  int tests;
  scanf("%d", &tests);
  for (int test = 0; test < tests; ++test) {
    vector<unsigned> a(n);

    int index = 0;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        int b;
        scanf("%d", &b);
        a[index] |= b * (1 << n);
        a[index] |= (1 << index);
        if (i > 0) {
          a[index] |= (1 << (index - c));
        }
        if (i + 1 < r) {
          a[index] |= (1 << (index + c));
        }
        if (j > 0) {
          a[index] |= (1 << (index - 1));
        }
        if (j + 1 < c) {
          a[index] |= (1 << (index + 1));
        }
        index++;
      }
    }

    unsigned x;
    bool solvable = SolveXorEquations(a, x);
    assert(solvable);

    printf("PUZZLE #%d\n", test + 1);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (j > 0) {
          printf(" ");
        }
        printf("%d", (x >> (i * c + j)) & 1);
      }
      printf("\n");
    }
  }
}

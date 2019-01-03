#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

static const int r = 5;
static const int c = 6;
static const int n = r * c;

void GaussianElimination(vector<vector<int> >& a, vector<int>& b) {
  int i = 0;
  for (int j = 0; j < n; ++j) {
    int i2 = i;
    while (i2 < n && a[i2][j] == 0) {
      ++i2;
    }
    if (i2 >= n) {
      continue;
    }
    if (i != i2) {
      swap(a[i], a[i2]);
      swap(b[i], b[i2]);
    }
    assert(a[i][j] == 1);
    for (i2 = i + 1; i2 < n; ++i2) {
      if (a[i2][j] == 1) {
        for (int j2 = j; j2 < n; ++j2) {
          a[i2][j2] ^= a[i][j2];
        }
        b[i2] ^= b[i];
      }
    }
    ++i;
  }
}

bool SolveXorEquations(vector<vector<int> >& a, vector<int>& b,
                       vector<int>& x) {
  GaussianElimination(a, b);

  x.resize(n);
  fill(x.begin(), x.end(), 0);
  for (int i = n - 1; i >= 0; --i) {
    int j = 0;
    while (j < n && a[i][j] == 0) {
      ++j;
    }

    if (j >= n) {
      if (b[i] == 1) {
        return false;
      }
      continue;
    }

    x[j] = b[i];
    for (int j2 = j + 1; j2 < n; ++j2) {
      x[j] ^= x[j2] * a[i][j2];
    }
  }
  return true;
}

int main() {
  int tests;
  scanf("%d", &tests);
  for (int test = 0; test < tests; ++test) {
    vector<vector<int> > a(n, vector<int>(n));
    vector<int> b(n);

    int index = 0;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        scanf("%d", &b[index]);
        a[index][index] = 1;
        if (i > 0) {
          a[index][index - c] = 1;
        }
        if (i + 1 < r) {
          a[index][index + c] = 1;
        }
        if (j > 0) {
          a[index][index - 1] = 1;
        }
        if (j + 1 < c) {
          a[index][index + 1] = 1;
        }
        index++;
      }
    }

    vector<int> x;
    bool solvable = SolveXorEquations(a, b, x);
    assert(solvable);

    printf("PUZZLE #%d\n", test + 1);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (j > 0) {
          printf(" ");
        }
        printf("%d", x[i * c + j]);
      }
      printf("\n");
    }
  }
}

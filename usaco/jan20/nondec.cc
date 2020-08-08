#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

constexpr int kModulo = 1000000007;

class Matrix : public vector<vector<int> > {
 public:
  explicit Matrix(int n) : vector<vector<int> >(n, vector<int>(n)) {}
  static Matrix One(int n) {
    Matrix one(n);
    for (int x = 0; x < n; x++) {
      one[x][x] = 1;
    }
    return one;
  }

  Matrix operator*(const Matrix& other) const {
    const int n = size();
    Matrix m(n);
    for (int z = 0; z < n; z++) {
      for (int y = 0; y < n; y++) {
        if (other[z][y] == 0) {
          continue;
        }
        for (int x = 0; x < n; x++) {
          m[x][y] =
              (m[x][y] + (long long)(*this)[x][z] * other[z][y] % kModulo) %
              kModulo;
        }
      }
    }
    return m;
  }

  Matrix Inverse() const {
    const int n = size();

    Matrix left = *this;
    Matrix right = Matrix::One(n);
    for (int x = 0; x < n; x++) {
      int x2 = x;
      while (x2 < n && left[x2][x] == 0) {
        x2++;
      }
      if (x != x2) {
        left[x].swap(left[x2]);
        right[x].swap(right[x2]);
      }

      int inverse;
      int ignore;
      GCD(left[x][x], kModulo, &inverse, &ignore);
      inverse = (inverse + kModulo) % kModulo;
      for (int y = x; y < n; y++) {
        left[x][y] = (long long)left[x][y] * inverse % kModulo;
      }
      for (int y = 0; y < n; y++) {
        right[x][y] = (long long)right[x][y] * inverse % kModulo;
      }
      for (x2 = x + 1; x2 < n; x2++) {
        int multiplier = left[x2][x];
        if (multiplier == 0) {
          continue;
        }
        for (int y = x; y < n; y++) {
          left[x2][y] =
              (left[x2][y] - (long long)left[x][y] * multiplier % kModulo +
               kModulo) %
              kModulo;
        }
        for (int y = 0; y < n; y++) {
          right[x2][y] =
              (right[x2][y] - (long long)right[x][y] * multiplier % kModulo +
               kModulo) %
              kModulo;
        }
      }
    }

    for (int y = n - 1; y >= 0; y--) {
      for (int x = 0; x < y; x++) {
        int multiplier = left[x][y];
        if (multiplier == 0) {
          continue;
        }
        left[x][y] = 0;
        for (int y2 = 0; y2 < n; y2++) {
          right[x][y2] =
              (right[x][y2] - (long long)right[y][y2] * multiplier % kModulo +
               kModulo) %
              kModulo;
        }
      }
    }

    return right;
  }

 private:
  static int GCD(int a, int b, int* x, int* y) {
    if (b == 0) {
      *x = 1;
      *y = 0;
      return a;
    }

    int x2;
    int y2;
    int g = GCD(b, a % b, &x2, &y2);
    *x = y2;
    *y = x2 - a / b * y2;
    return g;
  }

  friend ostream& operator<<(ostream& os, const Matrix&);
};

ostream& operator<<(ostream& os, const Matrix& m) {
  const int n = m.size();
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      os << m[x][y] << ' ';
    }
    if (x < n - 1) {
      os << endl;
    }
  }
  return os;
}

class Solution {
 public:
  Solution(vector<int> a, const int k) {
    // m[i][j] = m[i-1][j] + (m[i-1][a[i-1]] if j >= a[i])
    const int n = a.size();
    prefix_product_.reserve(n + 1);
    prefix_product_.push_back(Matrix::One(k));
    for (int i = 1; i <= n; i++) {
      Matrix transfer = Matrix::One(k);
      for (int y = a[i - 1]; y < k; y++) {
        transfer[a[i - 1]][y]++;
      }
      prefix_product_.push_back(prefix_product_[i - 1] * transfer);
    }

    flattened_inverse_prefix_product_.reserve(n + 1);
    for (int i = 0; i <= n; i++) {
      Matrix inverse_prefix_product = prefix_product_[i].Inverse();
      vector<int> flattened(k);
      for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
          flattened[y] = (flattened[y] + inverse_prefix_product[x][y]) % kModulo;
        }
      }
      flattened_inverse_prefix_product_.push_back(flattened);
    }
  }

  int NumNonDecreasing(const int left, const int right) {
    const vector<int>& v = flattened_inverse_prefix_product_[left];
    const Matrix& m = prefix_product_[right + 1];
    const int k = v.size();
    int sum = 0;
    for (int x = 0; x < k; x++) {
      sum = (sum + (long long)v[x] * m[x][k - 1] % kModulo) % kModulo;
    }
    return sum;
  }

 private:
  vector<Matrix> prefix_product_;
  vector<vector<int>> flattened_inverse_prefix_product_;
};

int main() {
  ifstream fin("nondec.in");
  int n;
  int k;
  fin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
    a[i]--;
  }

  Solution s(move(a), k);

  ofstream fout("nondec.out");
  int num_queries;
  fin >> num_queries;
  for (int i = 0; i < num_queries; i++) {
    int left;
    int right;
    fin >> left >> right;
    left--;
    right--;
    fout << s.NumNonDecreasing(left, right) << endl;
  }

  return 0;
}
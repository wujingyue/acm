#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

constexpr int kModulo = 1000000007;
constexpr int kMaxN = 20;

class Matrix {
 public:
  explicit Matrix(int n) : n_(n) {
    for (array<int, kMaxN>& row : m_) {
      fill(row.begin(), row.end(), 0);
    }
  }

  static Matrix One(int n) {
    Matrix one(n);
    for (int x = 0; x < n; x++) {
      one.m_[x][x] = 1;
    }
    return one;
  }

  Matrix(const Matrix& other) = default;
  Matrix(Matrix&& other) = default;
  Matrix& operator=(Matrix&& other) = default;

  const array<int, kMaxN>& operator[](size_t i) const {
    return m_[i];
  }

  array<int, kMaxN>& operator[](size_t i) {
    return m_[i];
  }

  int Size() const { return n_; }

  void MultiplyLeftSparse(const Matrix& left) {
    Matrix temp(n_);
    for (int z = 0; z < n_; z++) {
      for (int x = 0; x < n_; x++) {
        const long long e = left[x][z];
        if (e == 0) {
          continue;
        }
        for (int y = 0; y < n_; y++) {
          temp[x][y] = (temp[x][y] + e * (*this)[z][y] % kModulo) % kModulo;
        }
      }
    }
    m_.swap(temp.m_);
  }

  void MultiplyRightSparse(const Matrix& right) {
    Matrix temp(n_);
    for (int z = 0; z < n_; z++) {
      for (int y = 0; y < n_; y++) {
        const long long e = right[z][y];
        if (e == 0) {
          continue;
        }
        for (int x = 0; x < n_; x++) {
          temp[x][y] = (temp[x][y] + e * (*this)[x][z] % kModulo) % kModulo;
        }
      }
    }
    m_.swap(temp.m_);
  }

  Matrix Inverse() const {
    Matrix left = *this;
    Matrix right = Matrix::One(n_);
    for (int x = 0; x < n_; x++) {
      int x2 = x;
      while (x2 < n_ && left[x2][x] == 0) {
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
      for (int y = x; y < n_; y++) {
        left[x][y] = (long long)left[x][y] * inverse % kModulo;
      }
      for (int y = 0; y < n_; y++) {
        right[x][y] = (long long)right[x][y] * inverse % kModulo;
      }
      for (x2 = x + 1; x2 < n_; x2++) {
        int multiplier = left[x2][x];
        if (multiplier == 0) {
          continue;
        }
        for (int y = x; y < n_; y++) {
          left[x2][y] =
              (left[x2][y] - (long long)left[x][y] * multiplier % kModulo +
               kModulo) %
              kModulo;
        }
        for (int y = 0; y < n_; y++) {
          right[x2][y] =
              (right[x2][y] - (long long)right[x][y] * multiplier % kModulo +
               kModulo) %
              kModulo;
        }
      }
    }

    for (int y = n_ - 1; y >= 0; y--) {
      for (int x = 0; x < y; x++) {
        int multiplier = left[x][y];
        if (multiplier == 0) {
          continue;
        }
        left[x][y] = 0;
        for (int y2 = 0; y2 < n_; y2++) {
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

  array<array<int, kMaxN>, kMaxN> m_;
  int n_;
};

ostream& operator<<(ostream& os, const Matrix& m) {
  const int n = m.Size();

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
    prefix_product_rightmost_column_.resize(n + 1);
    flattened_inverse_prefix_product_.resize(n + 1);

    Matrix prefix_product = Matrix::One(k);
    Matrix inverse_prefix_product = Matrix::One(k);
    prefix_product_rightmost_column_[0] = RightmostColumn(prefix_product);
    flattened_inverse_prefix_product_[0] = Flatten(inverse_prefix_product);

    for (int i = 1; i <= n; i++) {
      Matrix transfer = Matrix::One(k);
      for (int y = a[i - 1]; y < k; y++) {
        transfer[a[i - 1]][y]++;
      }
      prefix_product.MultiplyRightSparse(transfer);
      inverse_prefix_product.MultiplyLeftSparse(transfer.Inverse());
      prefix_product_rightmost_column_[i] = RightmostColumn(prefix_product);
      flattened_inverse_prefix_product_[i] = Flatten(inverse_prefix_product);
    }
  }

  int NumNonDecreasing(const int left, const int right) {
    const vector<int>& v1 = flattened_inverse_prefix_product_[left];
    const vector<int>& v2 = prefix_product_rightmost_column_[right + 1];
    assert(v1.size() == v2.size());

    const int k = v1.size();
    int sum = 0;
    for (int x = 0; x < k; x++) {
      sum = (sum + (long long)v1[x] * v2[x] % kModulo) % kModulo;
    }
    return sum;
  }

 private:
  static vector<int> Flatten(const Matrix& m) {
    const int n = m.Size();
    vector<int> flattened(n);
    for (int y = 0; y < n; y++) {
      int sum = 0;
      for (int x = 0; x < n; x++) {
        sum = (sum + m[x][y]) % kModulo;
      }
      flattened[y] = sum;
    }
    return flattened;
  }

  static vector<int> RightmostColumn(const Matrix& m) {
    const int n = m.Size();
    vector<int> rightmost_column(n);
    for (int x = 0; x < n; x++) {
      rightmost_column[x] = m[x][n - 1];
    }
    return rightmost_column;
  }

  vector<vector<int> > prefix_product_rightmost_column_;
  vector<vector<int> > flattened_inverse_prefix_product_;
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
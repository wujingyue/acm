#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution(const int n)
      : n_(n),
        prefix_sum_major_(n, vector<int>(n)),
        prefix_sum_minor_(n, vector<int>(n)) {}

  int CountTriangles(const vector<string>& a) {
    for (int x = 0; x < n_; x++) {
      for (int y = 0; y < n_; y++) {
        if (x - 1 >= 0 && y - 1 >= 0) {
          prefix_sum_major_[x][y] = prefix_sum_major_[x - 1][y - 1];
        } else {
          prefix_sum_major_[x][y] = 0;
        }
        prefix_sum_major_[x][y] += (a[x][y] == '*');
      }
    }
    for (int x = 0; x < n_; x++) {
      for (int y = 0; y < n_; y++) {
        if (x - 1 >= 0 && y + 1 < n_) {
          prefix_sum_minor_[x][y] = prefix_sum_minor_[x - 1][y + 1];
        } else {
          prefix_sum_minor_[x][y] = 0;
        }
        prefix_sum_minor_[x][y] += (a[x][y] == '*');
      }
    }

    int count = 0;
    for (int x = 0; x < n_; x++) {
      for (int y = 0; y < n_; y++) {
        if (a[x][y] == '.') {
          continue;
        }
        for (int d = 1; x + d < n_ && y + d < n_; d++) {
          const int x2 = x + d;
          const int y2 = y + d;
          if (a[x2][y2] == '.') {
            continue;
          }
          count += SumMajorSegment(x - d + 1, y2 + 1, x, y2 + d);
          count += SumMajorSegment(x2 + 1, y - d + 1, x2 + d, y);
        }
      }
    }
    for (int x = 0; x < n_; x++) {
      for (int y = 0; y < n_; y++) {
        if (a[x][y] == '.') {
          continue;
        }
        for (int d = 1; x + d < n_ && y - d >= 0; d++) {
          const int x2 = x + d;
          const int y2 = y - d;
          if (a[x2][y2] == '.') {
            continue;
          }
          count += SumMinorSegment(x - d + 1, y2 - 1, x - 1, y2 - d + 1);
          count += SumMinorSegment(x2, y + d, x2 + d, y);
        }
      }
    }
    return count;
  }

 private:
  int SumMajorSegment(int x1, int y1, int x2, int y2) {
    // x1 + t >= 0
    // y1 + t >= 0
    // t >= -x1
    // t >= -y1
    int t = Max3(0, -x1, -y1);
    x1 += t;
    y1 += t;

    // x2 - t <= n - 1
    // y2 - t <= n - 1
    // t >= x2 - n + 1
    // t >= y2 - n + 1
    t = Max3(0, x2 - n_ + 1, y2 - n_ + 1);
    x2 -= t;
    y2 -= t;

    if (x1 > x2 || y1 > y2) {
      return 0;
    }

    t = prefix_sum_major_[x2][y2];
    if (x1 - 1 >= 0 && y1 - 1 >= 0) {
      t -= prefix_sum_major_[x1 - 1][y1 - 1];
    }
    return t;
  }

  int SumMinorSegment(int x1, int y1, int x2, int y2) {
    // x1 + t >= 0
    // y1 - t <= n - 1
    // t >= -x1
    // t >= y1 - n + 1
    int t = Max3(0, -x1, y1 - n_ + 1);
    x1 += t;
    y1 -= t;

    // x2 - t <= n - 1
    // y2 + t >= 0
    // t >= x2 - n + 1
    // t >= -y2
    t = Max3(0, x2 - n_ + 1, -y2);
    x2 -= t;
    y2 += t;

    if (x1 > x2 || y1 < y2) {
      return 0;
    }

    t = prefix_sum_minor_[x2][y2];
    if (x1 - 1 >= 0 && y1 + 1 < n_) {
      t -= prefix_sum_minor_[x1 - 1][y1 + 1];
    }
    return t;
  }

  static int Max3(int a, int b, int c) { return max(max(a, b), c); }

  const int n_;
  vector<vector<int> > prefix_sum_major_;
  vector<vector<int> > prefix_sum_minor_;
};

class SlowSolution {
 public:
  int CountTriangles(const vector<string>& a) {
    const int n = a.size();

    int count = 0;
    for (int x1 = 0; x1 < n; x1++) {
      for (int y1 = 0; y1 < n; y1++) {
        for (int x2 = 0; x2 < n; x2++) {
          for (int y2 = 0; y2 < n; y2++) {
            for (int x3 = 0; x3 < n; x3++) {
              for (int y3 = 0; y3 < n; y3++) {
                if (make_pair(x1, y1) >= make_pair(x2, y2)) {
                  continue;
                }
                if (make_pair(x2, y2) >= make_pair(x3, y3)) {
                  continue;
                }
                if (a[x1][y1] == '.' || a[x2][y2] == '.' || a[x3][y3] == '.') {
                  continue;
                }
                int d = Distance(x1, y1, x2, y2);
                if (Distance(x1, y1, x3, y3) != d) {
                  continue;
                }
                if (Distance(x2, y2, x3, y3) != d) {
                  continue;
                }
                cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x3
                     << ' ' << y3 << endl;
                count++;
              }
            }
          }
        }
      }
    }
    return count;
  }

 private:
  static int Distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }
};

int main() {
  ifstream fin("triangles.in");
  int n;
  fin >> n;
  vector<string> a(n);
  for (int x = 0; x < n; x++) {
    fin >> a[x];
  }

  ofstream fout("triangles.out");
  Solution s(n);
  fout << s.CountTriangles(a) << endl;

  return 0;
}

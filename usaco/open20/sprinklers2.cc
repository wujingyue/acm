#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution() : multipliers_(kMaxN + 1) {
    multipliers_[0] = 1;
    for (int i = 1; i <= kMaxN; i++) {
      multipliers_[i] = multipliers_[i - 1] * 2 % kModulo;
    }
  }

  int NumPossibilities(const vector<string>& a) {
    const int n = a.size();

    // m[i][j] represents the number of possibilities when the divide in row i
    // is at column j. The divide of a row is defined as the column of the
    // leftmost cell that grows A. All the C cells up to row i are covered by C
    // sprinklers. All the A cells to the left of column j are covered by A
    // sprinklers. The A cells in column j..n-1 are not necessarily covered by A
    // sprinklers.
    vector<int> m(n + 1);
    {
      int num_empties = count(a[0].begin(), a[0].end(), '.');
      m[0] = LeftShift(1, num_empties);
      for (int j = 1; j <= n; j++) {
        if (a[0][j - 1] == '.') {
          m[j] = LeftShift(1, num_empties - 1);
        }
      }
    }

    for (int i = 1; i < n; i++) {
      int num_empties = count(a[i].begin(), a[i].end(), '.');
      for (int j = n; j >= 0; j--) {
        m[j] = LeftShift(m[j], num_empties);
        if (j == 0 || a[i][j - 1] == 'W') {
          continue;
        }
        if (num_empties < 2) {
          assert(num_empties == 1);
        }
        for (int j2 = 0; j2 < j; j2++) {
          if (a[i - 1][j2] == '.') {
            m[j] = (m[j] + (num_empties == 1
                                ? DivideByTwo(m[j2])
                                : LeftShift(m[j2], num_empties - 2))) %
                   kModulo;
          }
        }
      }
    }

    int possibilities = 0;
    for (int j = 0; j < n; j++) {
      if (a[n - 1][j] == '.') {
        possibilities = (possibilities + DivideByTwo(m[j])) % kModulo;
      }
    }
    return (possibilities + m[n]) % kModulo;
  }

 private:
  int DivideByTwo(int x) {
    if (x % 2 == 0) {
      return x / 2;
    } else {
      return (x + kModulo) / 2;
    }
  }

  int LeftShift(int x, int k) {
    return (long long)x * multipliers_[k] % kModulo;
  }

  vector<int> multipliers_;
  static constexpr int kModulo = 1000000007;
  static constexpr int kMaxN = 2000;
};

int main() {
  ifstream fin("sprinklers2.in");
  int n;
  fin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
    assert(a[i].length() == n);
  }

  ofstream fout("sprinklers2.out");
  Solution s;
  fout << s.NumPossibilities(a) << endl;
}

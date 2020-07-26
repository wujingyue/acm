#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

constexpr int kModulo = 1000000007;

int main() {
  ifstream fin("help.in");
  int n;
  int k;
  fin >> n >> k;
  vector<pair<int, int>> s(n);
  for (int i = 0; i < n; i++) {
    fin >> s[i].first >> s[i].second;
  }

  sort(s.begin(), s.end());

  vector<vector<int>> m(n + 1, vector<int>(n + 1));
  m[n][0] = 1;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 1; j <= n; j++) {
      int two_to_included = 1;
      for (int i2 = i + 1; i2 <= n; i2++) {
        if (i2 < n && s[i2].second < s[i].second) {
          two_to_included = two_to_included * 2 % kModulo;
          continue;
        }
        
        if (i2 < n && s[i2].first < s[i].second) {
          m[i][j] = (m[i][j] + (long long)two_to_included * m[i2][j] % kModulo) % kModulo;
        } else {
          m[i][j] = (m[i][j] + (long long)two_to_included * m[i2][j - 1] % kModulo) % kModulo;
        }
      }
    }
  }

  int answer = 0;
  for (int j = 1; j <= n; j++) {
    int power = 1;
    for (int t = 0; t < k; t++) {
      power = (long long)power * j % kModulo;
    }
    for (int i = 0; i < n; i++) {
      answer = (answer + (long long)m[i][j] * power) % kModulo;
    }
  }

  ofstream fout("help.out");
  fout << answer << endl;

  return 0;
}
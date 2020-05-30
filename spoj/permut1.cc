#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> NumPermutationsWithInversions(int n, int k) {
  vector<vector<int>> m(n + 1, vector<int>(k + 1));
  m[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      if (m[i][j] == 0) {
        continue;
      }
      for (int j2 = j; j2 <= min(j + i, k); j2++) {
        m[i + 1][j2] += m[i][j];
      }
    }
  }
  return m;
}

int main() {
  vector<vector<int>> m = NumPermutationsWithInversions(12, 98);
  int num_tests;
  cin >> num_tests;
  for (int i = 0; i < num_tests; i++) {
    int n;
    int k;
    cin >> n >> k;
    cout << m[n][k] << endl;
  }
  return 0;
}

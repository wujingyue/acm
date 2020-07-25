#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int SumValidSteps(const int n, const int modulo) {
    vector<int> primes = FindAllPrimes(n);
    const int k = primes.size();

    vector<vector<int> > m(n + 1, vector<int>(k + 1));
    for (int i = 0; i <= n; i++) {
      m[i][k] = 1;
    }
    for (int j = k - 1; j >= 0; j--) {
      for (int i = 0; i <= n; i++) {
        m[i][j] = m[i][j + 1];
        long long power_of_pj = primes[j];
        while (i - power_of_pj >= 0) {
          m[i][j] =
              (m[i][j] + power_of_pj * m[i - power_of_pj][j + 1] % modulo) %
              modulo;
          power_of_pj = power_of_pj * primes[j] % modulo;
        }
      }
    }
    return m[n][0];
  }

 private:
  vector<int> FindAllPrimes(const int n) {
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
      if (IsPrime(i)) {
        primes.push_back(i);
      }
    }
    return primes;
  }

  bool IsPrime(const int i) {
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  ifstream fin("exercise.in");
  int n;
  int modulo;
  fin >> n >> modulo;

  Solution s;

  ofstream fout("exercise.out");
  fout << s.SumValidSteps(n, modulo) << endl;
  return 0;
}
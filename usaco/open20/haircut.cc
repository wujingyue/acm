#include <fstream>
#include <vector>

using namespace std;

class Solution {
  public:
  vector<int> ComputeLeftLarger(const vector<int>& a) {
    const int n = a.size();

    vector<int> left_larger(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (a[j] > a[i]) {
          left_larger[i]++;
        }
      }
    }
    return left_larger;
  }
};

int main() {
  ifstream fin("haircut.in");
  int n;
  fin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }

  Solution s;
  vector<int> left_larger = s.ComputeLeftLarger(a);

  vector<int> decrease_by(n + 1);
  for (int i = 0; i < n; i++) {
    decrease_by[a[i]] += left_larger[i];
  }
  ofstream fout("haircut.out");
  int num_inverse_pairs = 0;
  for (int j = 0; j < n; j++) {
    fout << num_inverse_pairs << endl;
    num_inverse_pairs += decrease_by[j];
  }

  return 0;
}
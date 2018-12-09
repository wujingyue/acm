#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int NumSegments(const vector<int>& cables, int len) {
  int num_segments = 0;
  for (size_t i = 0; i < cables.size(); ++i) {
    num_segments += cables[i] / len;
  }
  return num_segments;
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> cables;
  for (int i = 0; i < n; ++i) {
    float cable;
    cin >> cable;
    cables.push_back((int)(cable * 100));
  }

  int left = 0;
  int right = *max_element(cables.begin(), cables.end());
  while (left < right) {
    float mid = left + (right - left + 1) / 2;
    if (NumSegments(cables, mid) >= k) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }

  cout << fixed << setprecision(2) << (float)left / 100 << endl;
}
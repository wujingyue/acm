#include <iostream>
#include <vector>

using namespace std;

int SegmentsRequired(const vector<int>& a, int upper_bound) {
  int segments = 1;
  int sum_of_current_segment = a[0];
  for (int i = 1; i < a.size(); i++) {
    if (sum_of_current_segment + a[i] <= upper_bound) {
      sum_of_current_segment += a[i];
    } else {
      segments++;
      sum_of_current_segment = a[i];
    }
  }
  return segments;
}

int MinimumSegmentSum(const vector<int>& a, int m) {
  int left = 0;
  int right = 0;
  for (int i = 0; i < a.size(); i++) {
    left = max(left, a[i]);
    right += a[i];
  }
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (SegmentsRequired(a, mid) <= m) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    int expense;
    cin >> expense;
    a.push_back(expense);
  }
  cout << MinimumSegmentSum(a, m) << endl;
}
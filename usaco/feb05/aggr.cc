#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int NumCows(const vector<int>& stalls, int radius) {
  int last = 0;
  int num_cows = 1;
  for (int i = 1; i < stalls.size(); ++i) {
    if (stalls[last] + radius <= stalls[i]) {
      last = i;
      num_cows++;
    }
  }
  return num_cows;
}

int main() {
  int n;
  int c;
  scanf("%d %d", &n, &c);
  vector<int> stalls;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    stalls.push_back(x);
  }

  sort(stalls.begin(), stalls.end());

  int left = 1;  // leads to n cows.
  int right = stalls.back() - stalls.front();  // leads to 2 cows.
  // Find the largest R such that NumCows(stalls, R) >= c.
  while (left < right) {
    int mid = left + (right - left + 1) / 2;
    if (NumCows(stalls, mid) >= c) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }

  cout << left << endl;
}
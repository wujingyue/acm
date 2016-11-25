#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

constexpr int kMaxN = 2048;

int a[kMaxN];
int n;

bool CanBeIncreased(int s, int e) {
  return any_of(&a[s], &a[e + 1], [](int digit) { return digit < 9; });
}

void IncreaseToNextPalindrome(int s, int e, bool allow_equal) {
  if (s > e) {
    return;
  }

  if (s == e) {
    if (!allow_equal) {
      assert(a[s] < 9);
      ++a[s];
    }
    return;
  }

  if (a[s] == a[e]) {
    if (!allow_equal && !CanBeIncreased(s + 1, e - 1)) {
      ++a[s];
      ++a[e];
      fill(&a[s + 1], &a[e], 0);
    } else {
      IncreaseToNextPalindrome(s + 1, e - 1, allow_equal);
    }
  } else if (a[s] > a[e]) {
    a[e] = a[s];
    IncreaseToNextPalindrome(s + 1, e - 1, true);
  } else {
    if (CanBeIncreased(s + 1, e - 1)) {
      a[e] = a[s];
      IncreaseToNextPalindrome(s + 1, e - 1, false);
    } else {
      ++a[s];
      a[e] = a[s];
      fill(&a[s + 1], &a[e], 0);
    }
  }
}

int main() {
  string s;
  cin >> s;
  n = s.length();
  for (int i = 0; i < n; ++i) {
    a[i] = s[i] - '0';
  }

  IncreaseToNextPalindrome(0, n - 1, true);

  for (int i = 0; i < n; ++i) {
    cout << a[i];
  }
  cout << endl;
  return 0;
}

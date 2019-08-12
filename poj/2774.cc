#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Suffix {
  int index;
  int first;
  int second;

  bool operator<(const Suffix& other) const {
    return (first != other.first ? first < other.first : second < other.second);
  }
};

void BucketSort(vector<Suffix>& suffixes) {
  int n = suffixes.size();
  vector<Suffix> temp(n);
  vector<int> count(n + 1);
  for (int i = 0; i < n; i++) {
    // The second rank can be -1.
    count[suffixes[i].second + 1]++;
  }
  for (int j = 1; j <= n; j++) {
    count[j] += count[j - 1];
  }
  for (int i = n - 1; i >= 0; i--) {
    int radix = suffixes[i].second + 1;
    temp[--count[radix]] = suffixes[i];
  }

  fill(count.begin(), count.end(), 0);
  for (int i = 0; i < n; i++) {
    count[temp[i].first]++;
  }
  for (int j = 1; j < n; j++) {
    count[j] += count[j - 1];
  }
  for (int i = n - 1; i >= 0; i--) {
    int radix = temp[i].first;
    suffixes[--count[radix]] = temp[i];
  }
}

int LongestCommonPrefix(const string& a, const string& b) {
  if (a.empty() || b.empty()) {
    return 0;
  }

  string s = a;
  s += '$';
  s += b;
  int n = s.length();

  vector<Suffix> suffixes(n);
  for (int i = 0; i < n; i++) {
    suffixes[i].index = i;
    suffixes[i].first = s[i];
    suffixes[i].second = (i + 1 < n ? s[i + 1] : -1);
  }

  sort(suffixes.begin(), suffixes.end());
  vector<int> rank(n);

  for (int step = 2; step < n; step *= 2) {
    int prev_first = suffixes[0].first;
    suffixes[0].first = 0;
    for (int i = 1; i < n; i++) {
      bool same = (suffixes[i].first == prev_first &&
                   suffixes[i].second == suffixes[i - 1].second);
      prev_first = suffixes[i].first;
      suffixes[i].first = suffixes[i - 1].first + (same ? 0 : 1);
    }
    for (int i = 0; i < n; i++) {
      rank[suffixes[i].index] = suffixes[i].first;
    }
    if (suffixes[n - 1].first == n - 1) {
      // Break the loop if all ranks are distinct.
      break;
    }
    // TODO(jingyue): break the loop if max rank == n - 1.
    for (int i = 0; i < n; i++) {
      int j = suffixes[i].index + step;
      suffixes[i].second = (j >= n ? -1 : rank[j]);
    }
    BucketSort(suffixes);
  }

  vector<int> h(n, 0);
  int k = 0;
  for (int i = 0; i < n; i++) {
    // Calculate h[rank[i]].
    // Loop invariant: k = h[rank[i - 1]].
    if (rank[i] == 0) {
      continue;
    }
    int j = suffixes[rank[i] - 1].index;
    k = max(0, k - 1);
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
      k++;
    }
    h[rank[i]] = k;
  }

  int lcp = 0;
  for (int i = 1; i < n; i++) {
    if (h[i] > lcp && ((suffixes[i].index < a.length()) ^
                       (suffixes[i - 1].index < a.length()))) {
      lcp = h[i];
    }
  }
  return lcp;
}

int main() {
  string a;
  string b;
  getline(cin, a);
  getline(cin, b);
  cout << LongestCommonPrefix(a, b) << endl;
}

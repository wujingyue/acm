#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int> >;

// Returns a preorder of the tree.
vector<int> MakeTree(Graph& g, const int root) {
  const int n = g.size();

  vector<int> stack;
  vector<int> parent(n, -1);

  stack.push_back(root);
  parent[root] = root;

  vector<int> preorder;
  preorder.reserve(n);
  while (!stack.empty()) {
    const int x = stack.back();
    stack.pop_back();
    preorder.push_back(x);
    for (const int y : g[x]) {
      if (parent[y] == -1) {
        parent[y] = x;
        stack.push_back(y);
      }
    }
  }

  for (int x = 0; x < n; x++) {
    g[x].erase(remove(g[x].begin(), g[x].end(), parent[x]), g[x].end());
  }
  return preorder;
}

class Solution {
 public:
  Solution(const Graph& g, const vector<int>& preorder)
      : g_(g), preorder_(preorder) {}

  bool CanPartition(const int k) const {
    const int n = g_.size();
    const int root = preorder_.front();

    vector<int> m(n);
    vector<int> paths;
    paths.reserve(n);
    for (auto i = preorder_.rbegin(), e = preorder_.rend(); i != e; i++) {
      const int x = *i;
      paths.clear();
      for (const int y : g_[x]) {
        paths.push_back(m[y] + 1);
      }
      // TODO(jingyue): can be optimized using radix sort.
      sort(paths.begin(), paths.end());
      m[x] = FindMaxSoRestCanBePaired(paths, k, x == root);
      if (m[x] < 0) {
        return false;
      }
    }

    return m[root] == 0 || m[root] >= k;
  }

 private:
  // a must be sorted.
  int FindMaxSoRestCanBePaired(const vector<int>& a, const int k,
                               const bool target_zero) const {
    const int n = a.size();

    if (n % 2 == 1) {
      return FindMaxSoRestCanBePairedOdd(a, 0, n - 1, k);
    }

    // n is even.
    if (!target_zero && n > 0 && a[n - 1] >= k) {
      int m = FindMaxSoRestCanBePairedOdd(a, 0, n - 2, k);
      if (m >= 0) {
        return m;
      }
    }

    int i = 0;
    int j = n - 1;
    while (i < j && a[i] + a[j] >= k) {
      i++;
      j--;
    }
    return (i > j ? 0 : -1);
  }

  int FindMaxSoRestCanBePairedOdd(const vector<int>& a, const int left,
                                  const int right, const int k) const {
    vector<int> match(a.size());
    match[left] = -1;
    {
      int i = left + 1;
      int j = right;
      while (i < j) {
        if (a[i] + a[j] < k) {
          return -1;
        }
        match[i] = j;
        match[j] = i;
        i++;
        j--;
      }
    }

    for (int i = left; i + 1 <= right; i++) {
      // i is not paired and i+1 is.
      // Can we pair i instead of i+1 with match[i+1]?
      int j = match[i + 1];
      if (a[i] + a[j] < k) {
        return a[i];
      }
      match[i] = j;
      match[j] = i;
      match[i + 1] = -1;
    }
    return a[right];
  }

  const Graph& g_;
  const vector<int>& preorder_;
};

int main() {
  ifstream fin("deleg.in");
  int n;
  fin >> n;
  Graph g(n);
  for (int i = 0; i < n - 1; i++) {
    int x;
    int y;
    fin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> preorder = MakeTree(g, 0);

  Solution s(g, preorder);
  int low = 1;
  int high = n - 1;
  // OK, OK, not OK
  while (low < high) {
    int mid = low + (high - low + 1) / 2;
    if (s.CanPartition(mid)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }

  ofstream fout("deleg.out");
  fout << low << endl;
  return 0;
}

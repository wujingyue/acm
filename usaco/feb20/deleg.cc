#include <algorithm>
#include <cassert>
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
      if (x == root) {
        // The goal is to pair all child paths so require an even number of
        // child paths.
        if (g_[x].size() % 2 != 0) {
          paths.push_back(0);
        }
      } else {
        // The goal is to find the longest child path such that the rest can be
        // compared. So we require an odd number of child paths.
        if (g_[x].size() % 2 == 0) {
          paths.push_back(0);
        }
      }
      for (const int y : g_[x]) {
        paths.push_back(m[y] + 1);
      }

      sort(paths.begin(), paths.end());

      m[x] = Pair(paths, k, x != root);
      if (m[x] < 0) {
        return false;
      }
    }

    return m[root] == 0 || m[root] >= k;
  }

 private:
  // a must be sorted.
  static int Pair(const vector<int>& a, const int k, const bool find_longest) {
    const int n = a.size();

    if (find_longest) {
      assert(n % 2 == 1);
      vector<int> match(n);
      match[0] = -1;
      {
        int i = 1;
        int j = n - 1;
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

      for (int i = 0; i + 1 < n; i++) {
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
      return a[n - 1];
    } else {
      int i = 0;
      int j = n - 1;
      while (i < j && a[i] + a[j] >= k) {
        i++;
        j--;
      }
      return (i > j ? 0 : -1);
    }
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

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution(const vector<int>& parent, const vector<bool>& has_worm)
      : has_worm_(has_worm) {
    n_ = parent.size();
    assert(n_ == (int)has_worm.size());

    children_.resize(n_);
    root_ = -1;
    for (int x = 0; x < n_; x++) {
      if (parent[x] == -1) {
        root_ = x;
      } else {
        children_[parent[x]].push_back(x);
      }
    }

    num_leaves_.resize(n_, 0);
  }

  double Solve() {
    ComputeNumLeaves(root_);

    vector<double> m0(n_);
    vector<double> m1(n_);
    return ComputeExpectedTime(root_, m0, m1);
  }

 private:
  int ComputeNumLeaves(const int x) {
    int num = 0;
    if (children_[x].empty()) {
      num = 1;
    } else {
      num = 0;
      for (int j = 0, e = children_[x].size(); j < e; j++) {
        const int y = children_[x][j];
        num += ComputeNumLeaves(y);
      }
    }
    num_leaves_[x] = num;
    return num;
  }

  class Comparator {
   public:
    Comparator(const vector<int>& num_leaves, const vector<double>& m0)
        : num_leaves_(num_leaves), m0_(m0) {}

    bool operator()(const int y0, const int y1) const {
      return (m0_[y0] + 2) * num_leaves_[y1] < (m0_[y1] + 2) * num_leaves_[y0];
    }

   private:
    const vector<int>& num_leaves_;
    const vector<double>& m0_;
  };

  double ComputeExpectedTime(const int x, vector<double>& m0,
                           vector<double>& m1) {
    if (children_[x].empty()) {
      m0[x] = 0.0;
      return m1[x] = 0.0;
    }

    for (int j = 0, e = children_[x].size(); j < e; j++) {
      const int y = children_[x][j];
      ComputeExpectedTime(y, m0, m1);
    }

    m0[x] = 0.0;
    if (!has_worm_[x]) {
      for (int j = 0, e = children_[x].size(); j < e; j++) {
        const int y = children_[x][j];
        m0[x] += 1 + m0[y] + 1;
      }
    }

    vector<int> order = children_[x];
    sort(order.begin(), order.end(), Comparator(num_leaves_, m0));

    double wasted_time = 0.0;
    double expected_time = 0.0;
    for (int j = 0, e = order.size(); j < e; j++) {
      const int y = order[j];
      expected_time +=
          (wasted_time + 1 + m1[y]) * num_leaves_[y] / num_leaves_[x];
      wasted_time += 1 + m0[y] + 1;
    }
    return m1[x] = expected_time;
  }

  double Solve(const vector<int>& parent, const vector<bool>& has_worm) {
    const int n = parent.size();
    assert(n == (int)has_worm.size());

    vector<vector<int> > children(n);
    int root = -1;
    for (int x = 0; x < n; x++) {
      if (parent[x] == -1) {
        root = x;
      } else {
        children[parent[x]].push_back(x);
      }
    }

    vector<int> num_leaves(n);
    ComputeNumLeaves(root);

    vector<double> m0(n);
    vector<double> m1(n);
    return ComputeExpectedTime(root, m0, m1);
  }

  int n_;
  int root_;
  vector<vector<int> > children_;
  vector<int> num_leaves_;
  const vector<bool>& has_worm_;
};

int main() {
  int n;
  cin >> n;
  cout << fixed << setprecision(4);
  while (n > 0) {
    vector<int> parent(n);
    vector<bool> has_worm(n);
    for (int x = 0; x < n; x++) {
      cin >> parent[x];
      if (parent[x] > 0) {
        parent[x]--;
      }

      char c;
      cin >> c;
      has_worm[x] = (c == 'Y');
    }

    Solution s(parent, has_worm);
    cout << s.Solve() << endl;

    cin >> n;
  }

  return 0;
}
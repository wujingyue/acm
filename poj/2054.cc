#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int Solve(const vector<int>& cost_factor, const vector<vector<int> >& g,
            const int root) {
    vector<int> order;
    ComputeBestOrder(cost_factor, g, root, &order);

    const int n = cost_factor.size();
    int min_cost = 0;
    for (int i = 0; i < n; i++) {
      min_cost += cost_factor[order[i]] * (i + 1);
    }
    return min_cost;
  }

 private:
  void ComputeBestOrder(const vector<int>& cost_factor,
                        const vector<vector<int> >& g, const int x,
                        vector<int>* order) {
    // Leaf node.
    if (g[x].empty()) {
      order->push_back(x);
      return;
    }

    vector<int> child_order;
    ComputeBestOrder(cost_factor, g, g[x][0], &child_order);

    for (int j = 1, e = g[x].size(); j < e; j++) {
      vector<int> second_child_order;
      ComputeBestOrder(cost_factor, g, g[x][j], &second_child_order);
      Merge(child_order, second_child_order, cost_factor);
    }

    order->swap(child_order);
    order->insert(order->begin(), x);
  }

  void Merge(vector<int>& order1, const vector<int>& order2,
             const vector<int>& cost_factor) {
    const int n1 = order1.size();
    const int n2 = order2.size();
    // Can be optimized to O(n).
    vector<vector<int> > m(n1 + 1, vector<int>(n2 + 1));
    // Can be optimized to O(1).
    vector<vector<int> > suffix_sum(n1 + 1, vector<int>(n2 + 1));
    vector<vector<int> > c(n1 + 1, vector<int>(n2 + 1, -1));
    for (int i1 = n1; i1 >= 0; i1--) {
      for (int i2 = n2; i2 >= 0; i2--) {
        if (i1 == n1 && i2 == n2) {
          continue;
        }

        if (i1 < n1) {
          suffix_sum[i1][i2] = suffix_sum[i1 + 1][i2] + cost_factor[order1[i1]];
        } else {
          suffix_sum[i1][i2] = suffix_sum[i1][i2 + 1] + cost_factor[order2[i2]];
        }

        int min_value = INT_MAX;
        int choice = -1;
        if (i1 + 1 <= n1 && m[i1 + 1][i2] < min_value) {
          min_value = m[i1 + 1][i2];
          choice = 0;
        }
        if (i2 + 1 <= n2 && m[i1][i2 + 1] < min_value) {
          min_value = m[i1][i2 + 1];
          choice = 1;
        }
        m[i1][i2] = min_value + suffix_sum[i1][i2];
        c[i1][i2] = choice;
      }
    }

    {
      vector<int> merged_order;
      merged_order.reserve(n1 + n2);
      int i1 = 0;
      int i2 = 0;
      while (i1 < n1 || i2 < n2) {
        if (c[i1][i2] == 0) {
          merged_order.push_back(order1[i1]);
          i1++;
        } else {
          merged_order.push_back(order2[i2]);
          i2++;
        }
      }
      order1.swap(merged_order);
    }
  }
};

void ComputeParent(const vector<vector<int> >& g, const int x,
                   vector<int>& parent) {
  for (int j = 0, e = g[x].size(); j < e; j++) {
    const int y = g[x][j];
    if (parent[y] == -1) {
      parent[y] = x;
      ComputeParent(g, y, parent);
    }
  }
}

int main() {
  int n;
  int root;
  cin >> n >> root;
  while (n > 0 || root > 0) {
    root--;
    vector<int> cost_factor(n);
    for (int x = 0; x < n; x++) {
      cin >> cost_factor[x];
    }

    vector<vector<int> > g(n);
    for (int i = 0; i < n - 1; i++) {
      int x, y;
      cin >> x >> y;
      x--;
      y--;
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector<int> parent(n, -1);
    parent[root] = root;
    ComputeParent(g, root, parent);

    for (int x = 0; x < n; x++) {
      g[x].erase(remove(g[x].begin(), g[x].end(), parent[x]), g[x].end());
    }

    Solution s;
    cout << s.Solve(cost_factor, g, root) << endl;

    cin >> n >> root;
  }
  return 0;
}
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class DPSolution {
 public:
  int Solve(const vector<int>& cost_factor, const vector<vector<int> >& g,
            const vector<int>& parent, const int root) {
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

struct Set {
  Set(const int r, const int c)
      : size(1), sum(c), cost(c), parent(r) {}

  int size;
  int sum;
  int cost;
  int parent;
};

// A summary of Set used in the priority queue.
struct SetInfo {
  SetInfo(const int r, const Set& s) : root(r), size(s.size), sum(s.sum) {}

  bool operator<(const SetInfo& other) const {
    // priority_queue puts the largest element on top.
    // Set B should be merged before Set A iff B.sum / B.size > A.sum / A.size,
    // i.e., B.sum * A.size > A.sum * B.size.
    return other.sum * size > sum * other.size;
  }

  int root;
  int size;
  int sum;
};

class UnionFind {
 public:
  UnionFind(const vector<int>& cost_factor) {
    const int n = cost_factor.size();
    sets_.reserve(n);
    for (int x = 0; x < n; x++) {
      sets_.push_back(Set(x, cost_factor[x]));
    }
  }

  int GetRoot(const int x) {
    const int parent = sets_[x].parent;
    if (parent == x) {
      return x;
    }
    return sets_[x].parent = GetRoot(parent);
  }

  Set* GetSet(const int x) { return &sets_[x]; }

  int Union(const int x, const int y) {
    // cost0 = c0 + 2*c1 + 3*c2, sum0 = c0 + c1 + c2, n0 = 3
    // cost1 = c3 + 2*c4 + 3*c5, sum1 = c3 + c4 + c5, n1 = 3
    // merged cost = cost0 + cost1 + n0 * sum1
    int rx = GetRoot(x);
    int ry = GetRoot(y);
    Set* sx = &sets_[rx];
    Set* sy = &sets_[ry];

    sy->parent = rx;
    sx->cost += sy->cost + sx->size * sy->sum;
    sx->size += sy->size;
    sx->sum += sy->sum;
    return rx;
  }

 private:
  vector<Set> sets_;
};

class UnionFindSolution {
 public:
  int Solve(const vector<int>& cost_factor, const vector<vector<int> >& g,
            const vector<int>& parent, const int root) {
    const int n = cost_factor.size();

    UnionFind union_find(cost_factor);
    priority_queue<SetInfo> pq;

    // Pick the largest.
    // Merge with the set that contains its parent.
    for (int x = 0; x < n; x++) {
      pq.push(SetInfo(x, *union_find.GetSet(x)));
    }
    while (!pq.empty()) {
      const SetInfo top = pq.top();
      pq.pop();
      int ry = top.root;
      if (union_find.GetRoot(ry) != ry ||
          union_find.GetSet(ry)->size != top.size || parent[ry] == ry) {
        continue;
      }

      const int rx = union_find.Union(parent[ry], ry);
      pq.push(SetInfo(rx, *union_find.GetSet(rx)));
    }

    return union_find.GetSet(root)->cost;
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

    UnionFindSolution s;
    cout << s.Solve(cost_factor, g, parent, root) << endl;

    cin >> n >> root;
  }
  return 0;
}
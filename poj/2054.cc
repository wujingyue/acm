#include <algorithm>
#include <cassert>
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
  explicit Set(const int c) : size(1), sum(c), cost(c), pos_in_pq(-1) {}

  bool operator<(const Set& other) const {
    // Set A should be merged before Set B iff A.sum / A.size > B.sum / B.size,
    // i.e., A.sum * B.size > B.sum * A.size.
    return sum * other.size > other.sum * size;
  }

  bool operator<=(const Set& other) const { return !(other < *this); }

  int size;
  int sum;
  int cost;
  int pos_in_pq;
};

ostream& operator<<(ostream& os, const Set& s) {
  os << "[size = " << s.size << ", sum = " << s.sum << ", cost = " << s.cost
     << "]";
  return os;
}

class PriorityQueue {
 public:
  PriorityQueue(vector<Set>& sets) : sets_(sets) {}

  void Insert(const int x) {
    const int i = order_.size();
    order_.push_back(x);
    sets_[x].pos_in_pq = i;
    PercolateUp(i);
  }

  int Pop() { return Delete(0); }

  void Adjust(const int i) {
    PercolateUp(i);
    PercolateDown(i);
  }

  bool Empty() const { return order_.empty(); }

 private:
  int Delete(const int i) {
    assert(i >= 0 && i < (int)order_.size());
    const int x = order_[i];
    sets_[x].pos_in_pq = -1;

    const int y = order_.back();
    order_.pop_back();

    if (i < (int)order_.size()) {
      order_[i] = y;
      sets_[y].pos_in_pq = i;

      PercolateUp(i);
      PercolateDown(i);
    }
    return x;
  }

  void PercolateUp(int j) {
    int y = order_[j];
    while (j > 0) {
      int i = (j - 1) / 2;
      int x = order_[i];
      if (sets_[x] <= sets_[y]) {
        break;
      }
      order_[j] = x;
      sets_[x].pos_in_pq = j;

      j = i;
    }
    order_[j] = y;
    sets_[y].pos_in_pq = j;
  }

  void PercolateDown(int i) {
    const int n = order_.size();
    int x = order_[i];
    while (i * 2 + 1 < n) {
      int j = i * 2 + 1;
      if (j + 1 < n && sets_[order_[j + 1]] < sets_[order_[j]]) {
        j++;
      }
      int y = order_[j];
      if (sets_[x] <= sets_[y]) {
        break;
      }
      order_[i] = y;
      sets_[y].pos_in_pq = i;

      i = j;
    }
    order_[i] = x;
    sets_[x].pos_in_pq = i;
  }

  vector<int> order_;
  vector<Set>& sets_;
};

class UnionFind {
 public:
  UnionFind(const int n) : parent_(n) {
    for (int x = 0; x < n; x++) {
      parent_[x] = x;
    }
  }

  bool IsRoot(const int x) const { return parent_[x] == x; }

  int GetRoot(const int x) {
    const int parent = parent_[x];
    if (parent == x) {
      return x;
    }
    return parent_[x] = GetRoot(parent);
  }

  int Union(const int x, const int y) {
    const int rx = GetRoot(x);
    const int ry = GetRoot(y);
    parent_[ry] = rx;
    return rx;
  }

 private:
  vector<int> parent_;
};

class UnionFindSolution {
 public:
  int Solve(const vector<int>& cost_factor, const vector<vector<int> >& g,
            const vector<int>& parent, const int root) {
    const int n = cost_factor.size();

    UnionFind union_find(n);

    vector<Set> sets;
    sets.reserve(n);
    for (int x = 0; x < n; x++) {
      sets.push_back(Set(cost_factor[x]));
    }

    // Stores the roots of all unmerged sets except the tree root.
    PriorityQueue pq(sets);
    // TODO(jingyue): heapify in O(n) time.
    for (int x = 0; x < n; x++) {
      if (x != root) {
        pq.Insert(x);
      }
    }

    while (!pq.Empty()) {
      int ry = pq.Pop();
      const int rx = union_find.Union(parent[ry], ry);

      // cost0 = c0 + 2*c1 + 3*c2, sum0 = c0 + c1 + c2, n0 = 3
      // cost1 = c3 + 2*c4 + 3*c5, sum1 = c3 + c4 + c5, n1 = 3
      // merged cost = cost0 + cost1 + n0 * sum1
      Set* sx = &sets[rx];
      Set* sy = &sets[ry];
      sx->cost += sy->cost + sx->size * sy->sum;
      sx->size += sy->size;
      sx->sum += sy->sum;

      // The tree root is not in pq.
      if (sx->pos_in_pq >= 0) {
        pq.Adjust(sx->pos_in_pq);
      }
    }

    return sets[root].cost;
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

#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

constexpr int kMaxN = 8192;
constexpr int kMaxNeighborCount = 3;

int a[kMaxN][kMaxNeighborCount];
int depth[kMaxN];
int n;

void BreadthFirstSearch(int root) {
  deque<int> queue;
  queue.push_back(root);
  depth[root] = 0;
  while (!queue.empty()) {
    int x = queue.front();
    queue.pop_front();
    for (int j = 0; j < kMaxNeighborCount; ++j) {
      int y = a[x][j];
      if (y >= 0 && depth[y] < 0) {
        queue.push_back(y);
        depth[y] = depth[x] + 1;
      }
    }
  }
}

void PrintGroup(const vector<int>& group) {
  cout << group.size() << endl;
  if (group.size() > 0) {
    cout << group[0] + 1;
    for (size_t i = 1; i < group.size(); ++i) {
      cout << ' ' << group[i] + 1;
    }
    cout << endl;
  }
}

int main() {
  cin >> n;
  memset(a, -1, sizeof(a));
  for (int x = 0; x < n; ++x) {
    int neighbor_count = 0;
    cin >> neighbor_count;
    for (int i = 0; i < neighbor_count; ++i) {
      int y;
      cin >> y;
      --y;
      a[x][i] = y;
    }
  }

  memset(depth, -1, sizeof(depth));
  for (int x = 0; x < n; ++x) {
    if (depth[x] == -1) {
      BreadthFirstSearch(x);
    }
  }

  vector<int> partition;
  for (int x = 0; x < n; ++x) {
    partition.push_back(depth[x] % 2);
  }

  bool changed;
  do {
    changed = false;
    for (int x = 0; x < n; ++x) {
      int enemy_count =
          count_if(&a[x][0], &a[x][kMaxNeighborCount], [x, &partition](int y) {
            return y >= 0 && partition[x] == partition[y];
          });
      if (enemy_count > 1) {
        partition[x] = 1 - partition[x];
        changed = true;
      }
    }
  } while (changed);

  vector<int> group[2];
  for (int x = 0; x < n; ++x) {
    group[partition[x]].push_back(x);
  }
  if (group[0].size() < group[1].size()) {
    PrintGroup(group[0]);
  } else if (group[0].size() > group[1].size()) {
    PrintGroup(group[1]);
  } else {
    if (find(group[0].begin(), group[0].end(), 0) != group[0].end()) {
      PrintGroup(group[0]);
    } else {
      PrintGroup(group[1]);
    }
  }
  return 0;
}

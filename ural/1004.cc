#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> a;

void DepthFirstSearch(int x, const vector<int>& parent,
                      vector<pair<int, int>>* visited_time, int* now) {
  (*visited_time)[x].first = *now;
  ++(*now);
  for (int y = 0; y < n; ++y) {
    if ((*visited_time)[y].first == -1 && parent[y] == x) {
      DepthFirstSearch(y, parent, visited_time, now);
    }
  }
  (*visited_time)[x].second = *now;
  ++(*now);
}

std::tuple<vector<int>, vector<int>, vector<pair<int, int>>> Dijkstra(
    int root) {
  vector<int> shortest(n, numeric_limits<int>::max());
  vector<int> parent(n, -1);
  vector<int> visited(n, false);
  shortest[root] = 0;
  parent[root] = root;
  while (true) {
    int min_distance = numeric_limits<int>::max();
    int min_x = -1;
    for (int x = 0; x < n; ++x) {
      if (!visited[x] && shortest[x] < min_distance) {
        min_distance = shortest[x];
        min_x = x;
      }
    }
    if (min_x == -1)
      break;
    visited[min_x] = true;
    for (int y = 0; y < n; ++y) {
      if (a[min_x][y] < numeric_limits<int>::max()) {
        int candidate_distance = min_distance + a[min_x][y];
        if (candidate_distance < shortest[y]) {
          shortest[y] = candidate_distance;
          parent[y] = min_x;
        }
      }
    }
  }
  vector<pair<int, int>> visited_time(n, make_pair(-1, -1));
  int clock = 0;
  DepthFirstSearch(root, parent, &visited_time, &clock);
  return make_tuple(shortest, parent, visited_time);
}

vector<int> ComputePath(int from, int to, const vector<int>& parent) {
  vector<int> path;
  for (int x = from; x != to; x = parent[x]) {
    path.push_back(x);
  }
  path.push_back(to);
  return path;
}

bool Disjoint(const pair<int, int>& a, const pair<int, int>& b) {
  return a.second < b.first || b.second < a.first;
}

vector<int> FindShortestCycle() {
  int shortest_cycle_length = numeric_limits<int>::max();
  vector<int> shortest_cycle;
  for (int root = 0; root < n; ++root) {
    vector<int> shortest, parent;
    vector<pair<int, int>> visited_time;
    tie(shortest, parent, visited_time) = Dijkstra(root);
    for (int x = 0; x < n; ++x) {
      if (x == root) continue;
      for (int y = x + 1; y < n; ++y) {
        if (y == root || y == x) continue;
        if (shortest[x] < numeric_limits<int>::max() &&
            shortest[y] < numeric_limits<int>::max() &&
            a[x][y] < numeric_limits<int>::max() &&
            Disjoint(visited_time[x], visited_time[y])) {
          int length = shortest[x] + shortest[y] + a[x][y];
          if (length < shortest_cycle_length) {
            shortest_cycle_length = length;
            shortest_cycle = ComputePath(x, root, parent);
            vector<int> y_to_root = ComputePath(y, root, parent);
            for (auto i = y_to_root.rbegin() + 1; i != y_to_root.rend(); ++i) {
              shortest_cycle.push_back(*i);
            }
          }
        }
      }
    }
  }
  return shortest_cycle;
}

int main() {
  cin >> n;
  while (n > 0) {
    cin >> m;
    a.resize(n);
    for (int x = 0; x < n; ++x) {
      a[x].resize(n);
      fill(a[x].begin(), a[x].end(), numeric_limits<int>::max());
    }
    for (int i = 0; i < m; ++i) {
      int x, y, len;
      cin >> x >> y >> len;
      --x;
      --y;
      if (len < a[x][y]) {
        a[x][y] = len;
        a[y][x] = len;
      }
    }

    vector<int> shortest_cycle = FindShortestCycle();
    if (shortest_cycle.empty()) {
      cout << "No solution.\n";
    } else {
      bool first = true;
      for (int x : shortest_cycle) {
        if (first)
          first = false;
        else
          cout << ' ';
        cout << x + 1;
      }
      cout << "\n";
    }
    cin >> n;
  }
  return 0;
}

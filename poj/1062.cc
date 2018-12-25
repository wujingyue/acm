#include <climits>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int neighbor;
  int length;
};

typedef vector<vector<Edge> > Graph;

void AddEdge(int x, int y, int length, Graph* g) {
  g->at(x).push_back(Edge{y, length});
}

struct NodeAndDistance {
  int node;
  int distance;
  bool operator<(const NodeAndDistance& other) const {
    return distance > other.distance;
  }
};

int Dijkstra(const Graph& g, const vector<bool>& enabled, int start, int end) {
  vector<int> d(g.size(), INT_MAX);
  vector<bool> dequeued(g.size(), false);
  priority_queue<NodeAndDistance> q;

  if (enabled[start]) {
    q.push(NodeAndDistance{start, 0});
    d[start] = 0;
  }
  while (!q.empty()) {
    NodeAndDistance x = q.top();
    q.pop();
    if (dequeued[x.node]) {
      continue;
    }
    dequeued[x.node] = true;
    if (x.node == end) {
      return x.distance;
    }
    for (int i = 0; i < g[x.node].size(); ++i) {
      const Edge &edge_to_y = g[x.node][i];
      if (!enabled[edge_to_y.neighbor]) {
        continue;
      }
      NodeAndDistance y{edge_to_y.neighbor, x.distance + edge_to_y.length};
      if (y.distance < d[y.node]) {
        d[y.node] = y.distance;
        q.push(y);
      }
    }
  }
  return d[end];
}

int main() {
  int max_level_diff;
  int n;
  scanf("%d %d", &max_level_diff, &n);
  ++n;

  vector<int> level(n);
  Graph g(n);
  for (int x = 1; x < n; ++x) {
    int len;
    scanf("%d", &len);
    AddEdge(0, x, len, &g);
    scanf("%d", &level[x]);
    int incoming_edges;
    scanf("%d", &incoming_edges);
    for (int i = 0; i < incoming_edges; ++i) {
      int y;
      scanf("%d %d", &y, &len);
      AddEdge(y, x, len, &g);
    }
  }


  int min_cost = INT_MAX;
  vector<bool> enabled(n);
  for (int start = 0; start < n; ++start) {
    int start_level = level[start];
    enabled[0] = true;
    for (int i = 1; i < n; ++i) {
      enabled[i] = (level[i] >= start_level && level[i] <= start_level + max_level_diff);
    }
    min_cost = min(min_cost, Dijkstra(g, enabled, 0, 1));
  }
  printf("%d\n", min_cost);
}

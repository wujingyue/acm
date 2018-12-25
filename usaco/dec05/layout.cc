#include <cstdio>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int neighbor;
  int length;
};

typedef vector<vector<Edge> > Graph;

void AddEdge(int x, int y, int len, Graph* g) {
  Edge e;
  e.neighbor = y;
  e.length = len;
  g->at(x).push_back(e);
}

bool SPFA(const Graph& g, int start, vector<long long>* d) {
  int n = g.size();
  queue<int> q;
  vector<bool> in_queue(n);
  vector<int> num_dequeues(n);
  d->resize(n);
  fill(d->begin(), d->end(), LLONG_MAX);

  q.push(start);
  in_queue[start] = true;
  d->at(start) = 0;

  while (!q.empty()) {
    int x = q.front();
    q.pop();
    in_queue[x] = false;
    // Detect negative cycles that are reachable from `start`.
    num_dequeues[x]++;
    if (num_dequeues[x] > n) {
      return false;
    }
    for (int i = 0; i < g[x].size(); ++i) {
      const Edge& e = g[x][i];
      int y = e.neighbor;
      if (d->at(x) + e.length < d->at(y)) {
        d->at(y) = d->at(x) + e.length;
        if (!in_queue[y]) {
          q.push(y);
          in_queue[y] = true;
        }
      }
    }
  }
  return true;
}

int main() {
  int n, m_like, m_dislike;
  scanf("%d %d %d", &n, &m_like, &m_dislike);

  Graph g(n);
  for (int x = 0; x + 1 < n; ++x) {
    AddEdge(x + 1, x, 0, &g);
  }
  for (int i = 0; i < m_like; ++i) {
    int x, y, len;
    scanf("%d %d %d", &x, &y, &len);
    --x;
    --y;
    AddEdge(x, y, len, &g);
  }
  for (int i = 0; i < m_dislike; ++i) {
    int x, y, len;
    scanf("%d %d %d", &x, &y, &len);
    --x;
    --y;
    AddEdge(y, x, -len, &g);
  }

  vector<long long> d;
  if (!SPFA(g, 0, &d)) {
    printf("-1\n");
    return 0;
  }

  long long answer = d[n - 1];
  // Because n-1 reaches all nodes, SPFA from n-1 detects any negative cycle in
  // the whole graph. SPFA from 0 detects only negative cycles reachable from 0.
  if (!SPFA(g, n - 1, &d)) {
    printf("-1\n");
    return 0;
  }
  printf("%lld\n", answer == LLONG_MAX ? -2 : answer);
}

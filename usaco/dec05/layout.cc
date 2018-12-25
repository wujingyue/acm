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

// SPFA from nodes whose `d` is less than LLONG_MAX.
bool SPFA(const Graph& g, vector<long long>* d) {
  int n = g.size();
  queue<int> q;
  vector<bool> in_queue(n);
  vector<int> num_dequeues(n);

  for (int x = 0; x < n; ++x) {
    if (d->at(x) < LLONG_MAX) {
      q.push(x);
      in_queue[x] = true;
    }
  }

  while (!q.empty()) {
    int x = q.front();
    q.pop();
    in_queue[x] = false;
    // Found a negative cycle if any node is dequeued for more than n times.
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

  vector<long long> d(n, LLONG_MAX);
  d[0] = 0;
  if (!SPFA(g, &d)) {
    printf("-1\n");
    return 0;
  }

  long long answer = d[n - 1];
  // Set all d's to 0 and detect any negative cycle in the whole graph.  The
  // previous call to SPFA starts from 0 so it detects only negative cycles
  // reachable from 0.
  fill(d.begin(), d.end(), 0);
  if (!SPFA(g, &d)) {
    printf("-1\n");
    return 0;
  }
  printf("%lld\n", answer == LLONG_MAX ? -2 : answer);
}

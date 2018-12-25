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

bool BellmanFord(const Graph& g, int start, vector<long long>* d) {
  int n = g.size();
  queue<int> q;
  vector<bool> in_queue(n);
  vector<int> relaxes(n);
  d->resize(n, LLONG_MAX);

  q.push(start);
  in_queue[start] = true;
  d->at(start) = 0;

  while (!q.empty()) {
    int x = q.front();
    q.pop();
    in_queue[x] = false;
    for (int i = 0; i < g[x].size(); ++i) {
      const Edge& e = g[x][i];
      int y = e.neighbor;
      if (d->at(x) + e.length < d->at(y)) {
        d->at(y) = d->at(x) + e.length;
        if (!in_queue[y]) {
          q.push(y);
          in_queue[y] = true;
          relaxes[y]++;
          if (relaxes[y] > n) {
            return false;
          }
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
  if (BellmanFord(g, 0, &d)) {
    if (d[n - 1] == LLONG_MAX) {
      printf("-2\n");
    } else {
      printf("%lld\n", d[n - 1]);
    }
  } else {
    printf("-1\n");
  }
}

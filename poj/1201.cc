#include <climits>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int neighbor;
  int length;
};

typedef vector<vector<Edge>> Graph;

void AddEdge(int x, int y, int len, Graph *g) {
  Edge e;
  e.neighbor = y;
  e.length = len;

  if (x >= g->size()) {
    g->resize(x + 1);
  }
  g->at(x).push_back(e);
}

int main() {
  int m;
  scanf("%d", &m);

  int n = 0;
  Graph g;
  for (int i = 0; i < m; ++i) {
    int x, y, common;
    scanf("%d %d %d", &x, &y, &common);
    x++;
    y++;
    AddEdge(y, x - 1, -common, &g);
    n = max(n, y + 1);
  }
  for (int x = 0; x + 1 < n; ++x) {
    AddEdge(x + 1, x, 0, &g);
    AddEdge(x, x + 1, 1, &g);
  }
  g.resize(n);

  vector<bool> in_queue(n);
  vector<int> d(n, INT_MAX);
  queue<int> q;

  q.push(n - 1);
  d[n - 1] = 0;
  in_queue[n - 1] = true;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    in_queue[x] = false;

    for (int i = 0; i < g[x].size(); ++i) {
      const Edge &e = g[x][i];
      int y = e.neighbor;
      if (d[x] + e.length < d[y]) {
        d[y] = d[x] + e.length;
        if (!in_queue[y]) {
          in_queue[y] = true;
          q.push(y);
        }
      }
    }
  }

  printf("%d\n", -d[0]);
}

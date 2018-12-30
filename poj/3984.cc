#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int n = 5;
const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int maze[n][n];
int dir_arrived[n][n];

bool outside(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= n;
}

void BFS(int start_x, int start_y) {
  fill(&dir_arrived[0][0], &dir_arrived[n][0], -1);
  queue<pair<int, int> > q;
  q.push(make_pair(start_x, start_y));
  dir_arrived[start_x][start_y] = 4;
  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    for (int dir = 0;  dir < 4; ++dir) {
      int x2 = x + dirs[dir][0];
      int y2 = y + dirs[dir][1];
      if (!outside(x2, y2) && maze[x2][y2] == 0 && dir_arrived[x2][y2] == -1) {
        q.push(make_pair(x2, y2));
        dir_arrived[x2][y2] = dir;
      }
    }
  }
}

void Print(int x, int y) {
  vector<pair<int, int> > path;
  while (true) {
    path.push_back(make_pair(x, y));
    int dir = dir_arrived[x][y];
    if (dir == 4) {
      break;
    }
    x -= dirs[dir][0];
    y -= dirs[dir][1];
  }

  for (int i = path.size() - 1; i >= 0; --i) {
    printf("(%d, %d)\n", path[i].first, path[i].second);
  }
}

int main() {
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      cin >> maze[x][y];
    }
  }

  BFS(0, 0);

  Print(n - 1, n - 1);
}

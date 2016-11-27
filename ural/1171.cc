#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

constexpr int kHeight = 4;
constexpr int kWidth = 4;
constexpr int kSize = kHeight * kWidth;
constexpr int kMaxLevel = 16;
constexpr int kMaxDays = kMaxLevel * kSize;

const int kDeltaOfDir[4] = {-kWidth, 1, kWidth, -1};
const char kCharOfDir[5] = {'N', 'E', 'S', 'W', 'D'};

int food[kMaxLevel][kSize];
int max_food[kMaxLevel][kSize][kMaxDays + 1];
vector<int> path_on_this_level[kMaxLevel][kSize][kMaxDays + 1];

int local_max_food[kSize][kSize + 1];
int prev_dir[kSize][kSize + 1];

bool can_go_down[kMaxLevel][kSize];
int n;
int start;

// optimization
bool IsEntryOfTheLevel(int x, int level) {
  if (level == 0) {
    return x == start;
  }
  return can_go_down[level - 1][x];
}

bool IsValidMove(int x, int dir) {
  switch (dir) {
    case 0:
      return x / kWidth - 1 >= 0;
    case 1:
      return x % kWidth + 1 < kWidth;
    case 2:
      return x / kWidth + 1 < kHeight;
    case 3:
      return x % kWidth - 1 >= 0;
    default:
      assert(false && "Invalid direction");
  }
}

void ComputeLocalMaxFood(int x, int days, int collected_food, int level,
                         int visited) {
  for (int dir = 0; dir < 4; ++dir) {
    if (!IsValidMove(x, dir)) {
      continue;
    }
    int x1 = x + kDeltaOfDir[dir];
    assert(x1 >= 0 && x1 < kSize);
    if ((visited & (1 << x1)) == 0) {
      if (collected_food + food[level][x1] > local_max_food[x1][days + 1]) {
        local_max_food[x1][days + 1] = collected_food + food[level][x1];
        prev_dir[x1][days + 1] = dir;
      }
      // Continue search even if <= local_max_food. visited might be different.
      ComputeLocalMaxFood(x1, days + 1, collected_food + food[level][x1], level,
                          visited | (1 << x1));
    }
  }
}

vector<int> ComputeLocalPath(int x, int days) {
  vector<int> path;
  while (prev_dir[x][days] >= 0) {
    assert(x >= 0 && x < kSize);
    assert(days > 0);
    path.push_back(prev_dir[x][days]);
    x -= kDeltaOfDir[prev_dir[x][days]];
    --days;
  }
  reverse(path.begin(), path.end());
  return path;
}

vector<int> ComputeGlobalPath(int level, int x, int days) {
  vector<int> global_path;
  while (level >= 0) {
    const vector<int>& local_path = path_on_this_level[level][x][days];
    for (auto i = local_path.rbegin(); i != local_path.rend(); ++i) {
      global_path.push_back(*i);
      x -= kDeltaOfDir[*i];
      --days;
    }
    if (level > 0) {
      global_path.push_back(4);
      --days;
    }
    --level;
  }
  assert(days == 1);
  reverse(global_path.begin(), global_path.end());
  return global_path;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int x = 0; x < kSize; ++x) {
        cin >> food[i][x];
    }
    for (int x = 0; x < kSize; ++x) {
      cin >> can_go_down[i][x];
    }
  }
  int start_y, start_x;
  cin >> start_y >> start_x;
  --start_y;
  --start_x;
  start = start_y * kWidth + start_x;

  memset(max_food, -1, sizeof(max_food));
  for (int i = 0; i < n; ++i) {
    for (int x = 0; x < kSize; ++x) {
      if (!IsEntryOfTheLevel(x, i)) {
        continue;
      }

      // Compute local_max_food[x1][days].
      memset(local_max_food, -1, sizeof(local_max_food));
      local_max_food[x][1] = food[i][x];
      prev_dir[x][1] = -1;
      ComputeLocalMaxFood(x, /*days=*/1, /*collected_food=*/food[i][x], i,
                          /*visited=*/1 << x);

      // FIXME: merge
      if (i == 0) {
        for (int x1 = 0; x1 < kSize; ++x1) {
          for (int days = 1; days <= kSize; ++days) {
            if (local_max_food[x1][days] < 0) {
              continue;
            }
            max_food[0][x1][days] = local_max_food[x1][days];
            path_on_this_level[0][x1][days] = ComputeLocalPath(x1, days);
          }
        }
      } else {
        for (int days = 1; days <= i * kSize; ++days) {
          if (max_food[i - 1][x][days] < 0) {
            continue;
          }
          for (int x1 = 0; x1 < kSize; ++x1) {
            for (int local_days = 1; local_days <= kSize; ++local_days) {
              if (local_max_food[x1][local_days] < 0) {
                continue;
              }
              int candidate = max_food[i - 1][x][days] + local_max_food[x1][local_days];
              if (candidate > max_food[i][x1][days + local_days]) {
                max_food[i][x1][days + local_days] = candidate;
                path_on_this_level[i][x1][days + local_days] =
                    ComputeLocalPath(x1, local_days);
              }
            }
          }
        }
      }
    }
  }

  double max_ratio = numeric_limits<double>::lowest();
  vector<int> path_for_max_ratio;
  for (int x = 0; x < kSize; ++x) {
    for (int days = 1; days <= n * kSize; ++days) {
      if (max_food[n - 1][x][days] < 0) {
        continue;
      }
      double ratio = (double)max_food[n - 1][x][days] / days;
      if (ratio > max_ratio) {
        max_ratio = ratio;
        path_for_max_ratio = ComputeGlobalPath(n - 1, x, days);
        assert(path_for_max_ratio.size() == days - 1);
      }
    }
  }
  printf("%.4lf\n", max_ratio);
  printf("%ld\n", path_for_max_ratio.size());
  if (path_for_max_ratio.size() > 0) {
    for (int dir : path_for_max_ratio) {
      printf("%c", kCharOfDir[dir]);
    }
    printf("\n");
  }

  return 0;
}

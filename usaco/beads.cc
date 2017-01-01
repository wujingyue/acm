/*
ID: koalawj1
PROG: beads
LANG: C++11
*/

#include <cassert>
#include <fstream>

using namespace std;

constexpr int kMaxN = 512;

int color[kMaxN];
int next_of_color_clockwise[kMaxN][3], next_of_color_counterclockwise[kMaxN][3];
int n;

int Next(int i, int step) { return (i + step + n) % n; }

int NextOfColor(int i, int c, int step) {
  int j = Next(i, step);
  while (j != i && color[j] != c) {
    j = Next(j, step);
  }
  if (j == i && color[j] != c) {
    return -1;
  }
  return j;
}

int MergeColor(int c1, int c2) {
  assert(c1 >= 0 && c1 <= 2);
  assert(c2 >= 0 && c2 <= 2);
  if (c1 == 0) {
    return c2;
  }
  if (c2 == 0) {
    return c1;
  }
  return (c1 == c2 ? c1 : -1);
}

int CollectUntilColor(int i, int c, int step) {
  assert(c >= 1 && c <= 2);
  assert(step == -1 || step == 1);
  if (step == 1) {
    int j = next_of_color_clockwise[i][c];
    if (j == -1) {
      return n;
    } else {
      return (j - i + n) % n;
    }
  } else {
    int j = next_of_color_counterclockwise[i][c];
    if (j == -1) {
      return n;
    } else {
      return (i - j + n) % n;
    }
  }
}

int Collect(int i, int step) {
  if (color[i] == 0) {
    return max(CollectUntilColor(i, 1, step), CollectUntilColor(i, 2, step));
  } else {
    return CollectUntilColor(i, 3 - color[i], step);
  }
}

int main() {
  ifstream fin("beads.in");
  ofstream fout("beads.out");

  fin >> n;
  for (int i = 0; i < n; ++i) {
    char c;
    fin >> c;
    switch (c) {
      case 'w':
        color[i] = 0;
        break;
      case 'b':
        color[i] = 1;
        break;
      case 'r':
        color[i] = 2;
        break;
      default:
        assert(false && "wrong color");
    }
  }

  next_of_color_clockwise[n - 1][1] = NextOfColor(n - 1, 1, 1);
  next_of_color_clockwise[n - 1][2] = NextOfColor(n - 1, 2, 1);
  for (int i = n - 2; i >= 0; --i) {
    for (int c = 1; c <= 2; ++c) {
      next_of_color_clockwise[i][c] =
          (color[i + 1] == c ? i + 1 : next_of_color_clockwise[i + 1][c]);
    }
  }
  next_of_color_counterclockwise[0][1] = NextOfColor(0, 1, -1);
  next_of_color_counterclockwise[0][2] = NextOfColor(0, 2, -1);
  for (int i = 1; i < n; ++i) {
    for (int c = 1; c <= 2; ++c) {
      next_of_color_counterclockwise[i][c] =
          (color[i - 1] == c ? i - 1
                             : next_of_color_counterclockwise[i - 1][c]);
    }
  }

  int answer = 0;
  for (int breakpoint = 0; breakpoint < n; ++breakpoint) {
    answer = max(
        answer,
        min(n, Collect(breakpoint, 1) + Collect((breakpoint - 1 + n) % n, -1)));
  }
  fout << answer << endl;
  return 0;
}

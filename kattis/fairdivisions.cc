#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int CountFairDivisions(vector<pair<int, int>> points) {
    const int n = points.size();
    if (n % 2 != 0) {
      return 0;
    }

    sort(points.begin(), points.end(),
         [](const pair<int, int>& p1, const pair<int, int>& p2) {
           if (p1.second != p2.second) {
             return p1.second < p2.second;
           }
           return p1.first < p2.first;
         });

    vector<double> angles;
    angles.reserve(n);
    for (int i = 0; i + 1 < n; i++) {
      angles.push_back(GetAngle(points[i], points[i + 1]));
    }

    double last_min_angle = -DBL_MAX;

    int count = 0;
    while (true) {
#if 0
      for (const auto& p : points) {
        cerr << "(" << p.first << "," << p.second << ") ";
      }
      cerr << endl;
#endif

      double min_angle = DBL_MAX;
      for (int i = 0; i + 1 < n; i++) {
        if (angles[i] > last_min_angle && angles[i] < min_angle) {
          min_angle = angles[i];
        }
      }
      if (min_angle == DBL_MAX) {
        break;
      }

      for (int i = 0; i + 1 < n;) {
        if (angles[i] != min_angle) {
          i++;
          continue;
        }

        int j = i + 1;
        while (j + 1 < n && angles[j] == min_angle) {
          j++;
        }

        SwapRange(points, i, j);
        for (int k = max(i - 1, 0); k <= min(j, n - 2); k++) {
          angles[k] = GetAngle(points[k], points[k + 1]);
        }

        if (i < n / 2 && j >= n / 2) {
          count++;
        }

        i = j;
      }

      last_min_angle = min_angle;
    }
    return count;
  }

 private:
  static double GetAngle(const pair<int, int>& p1, const pair<int, int>& p2) {
    int x = p2.first - p1.first;
    int y = p2.second - p1.second;
    assert(x != 0 || y != 0);
    int g = GCD(abs(x), abs(y));
    x /= g;
    y /= g;
    double angle = atan2(y, x);
    if (angle < 0) {
      angle += M_PI * 2;
    }
    return angle;
  }

  static void SwapRange(vector<pair<int, int>>& points, int i, int j) {
    while (i < j) {
      swap(points[i], points[j]);
      i++;
      j--;
    }
  }

  static int GCD(int a, int b) {
    if (b == 0) {
      return a;
    }
    return GCD(b, a % b);
  }
};

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> points;
  points.reserve(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points.push_back(make_pair(x, y));
  }

  Solution s;
  cout << s.CountFairDivisions(points) << endl;

  return 0;
}
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <iostream>
#include <set>
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

    set<pair<double, int>> angles;
    for (int i = 0; i + 1 < n; i++) {
      angles.insert(make_pair(GetAngle(points[i], points[i + 1]), i));
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

      auto arg_min = angles.lower_bound(make_pair(last_min_angle, INT_MAX));
      if (arg_min == angles.end()) {
        break;
      }

      double min_angle = arg_min->first;
      vector<int> indices_to_flip;
      do {
        indices_to_flip.push_back(arg_min->second);
        arg_min = angles.erase(arg_min);
      } while (arg_min != angles.end() && arg_min->first == min_angle);

      int i = 0;
      while (i < (int)indices_to_flip.size()) {
        int j = i + 1;
        while (j < (int)indices_to_flip.size() && indices_to_flip[j - 1] + 1 == indices_to_flip[j]) {
          j++;
        }

        int s = indices_to_flip[i];
        int e = indices_to_flip[j - 1] + 1;
        if (s - 1 >= 0) {
          int removed = angles.erase(make_pair(GetAngle(points[s - 1], points[s]), s - 1));
          assert(removed == 1);
        }
        if (e + 1 < n) {
          int removed = angles.erase(make_pair(GetAngle(points[e], points[e + 1]), e));
          assert(removed == 1);
        }

        SwapRange(points, s, e);
        for (int k = max(s - 1, 0); k <= min(e, n - 2); k++) {
          angles.insert(make_pair(GetAngle(points[k], points[k + 1]), k));
        }

        if (s < n / 2 && e >= n / 2) {
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
#include <cfloat>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void UpdateIfSmaller(float& a, const float b) {
  if (b < a) {
    a = b;
  }
}

float Square(const float x) { return x * x; }

float Distance(const pair<int, int>& a, const pair<int, int>& b) {
  return sqrt(Square(a.first - b.first) + Square(a.second - b.second));
}

float ShortestTour(const vector<pair<int, int> >& p) {
  const int n = p.size();
  if (n == 1) {
    return 0.0;
  }

  vector<float> m(n, FLT_MAX);
  m[0] = Distance(p[0], p[1]);
  for (int j = 1; j + 1 < n; j++) {
    for (int i = j - 1; i >= 0; i--) {
      UpdateIfSmaller(m[j], m[i] + Distance(p[i], p[j + 1]));
      m[i] += Distance(p[j], p[j + 1]);
    }
  }

  float ans = FLT_MAX;
  for (int i = 0; i < n - 1; i++) {
    UpdateIfSmaller(ans, m[i] + Distance(p[i], p[n - 1]));
  }
  return ans;
}

int main() {
  int n;
  while (cin >> n) {
    vector<pair<int, int> > p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i].first >> p[i].second;
    }
    float ans = ShortestTour(p);
    printf("%.2f\n", ans);
  }
  return 0;
}

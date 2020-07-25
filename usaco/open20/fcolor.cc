#include <fstream>
#include <vector>

using namespace std;

class UnionFind {
 public:
  explicit UnionFind(const int n) : parent_(n) {
    for (int x = 0; x < n; x++) {
      parent_[x] = x;
    }
  }

  int Root(const int x) {
    if (x == -1) {
      return -1;
    }
    int& p = parent_[x];
    if (p == x) {
      return x;
    }
    return p = Root(p);
  }

  int Union(const int x, const int y) {
    const int rx = Root(x);
    const int ry = Root(y);
    parent_[ry] = rx;
    return rx;
  }

 private:
  vector<int> parent_;
};

class Solution {
 public:
  explicit Solution(const int n) : n_(n), uf_(n), admirer_(n, -1) {}

  // Add the fact that y admires x.
  void Admire(const int y, const int x) {
    int rx = uf_.Root(x);
    int ry = uf_.Root(y);
    int rz = uf_.Root(admirer_[rx]);
    if (rz == -1) {
      admirer_[rx] = ry;
      return;
    }

    // Both ry and rz admire rx.
    while (ry >= 0 && rz >= 0 && ry != rz) {
      uf_.Union(ry, rz);
      if (admirer_[ry] == -1) {
        admirer_[ry] = admirer_[rz];
      }
      ry = uf_.Root(admirer_[ry]);
      rz = uf_.Root(admirer_[rz]);
    }
  }

  vector<int> GetFavoriteColors() {
    vector<int> colors(n_, -1);
    int next_color = 0;
    for (int x = 0; x < n_; x++) {
      const int rx = uf_.Root(x);
      if (colors[rx] == -1) {
        colors[rx] = next_color;
        next_color++;
      }
      colors[x] = colors[rx];
    }
    return colors;
  }

 private:
  int n_;
  UnionFind uf_;
  vector<int> admirer_;
};

int main() {
  ifstream fin("fcolor.in");
  int n;
  int m;
  fin >> n >> m;
  Solution s(n);
  for (int i = 0; i < m; i++) {
    int x;
    int y;
    fin >> x >> y;
    x--;
    y--;
    s.Admire(y, x);
  }

  ofstream fout("fcolor.out");
  vector<int> colors = s.GetFavoriteColors();
  for (const int c : colors) {
    fout << c + 1 << endl;
  }
  return 0;
}
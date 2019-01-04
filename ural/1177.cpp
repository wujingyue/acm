#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long double Real;

const Real o = 1e-8;
const Real pi = acos(-1.0);

const int max_n = 128;

bool c[max_n][max_n];
bool inq[max_n * 2];
vector<string> a, b;
int m, n;
int T, I;

void parse(string str, vector<string> &a, bool pattern) {
  a.clear();
  a.push_back("");
  assert(str.length() >= 2);
  assert(str[0] == (char)39 && str[str.length() - 1] == char(39));
  str.erase(0, 1);
  str.erase(str.length() - 1);
  size_t i = 0;
  while (i + 1 < str.length()) {
    if (str[i] == (char)39 && str[i + 1] == (char)39) {
      str.erase(i, 1);
      ++i;
    } else
      ++i;
  }
  if (pattern) {
    while (str.length() > 0) {
      if (str[0] == '[') {
        i = 1;
        while (i < str.length() && str[i] != ']') i++;
        assert(i < str.length());
        string s = str.substr(1, i - 1);
        str.erase(0, i + 1);
        i = 0;
        while (i < s.length()) {
          if (s[i] == '-' && i > 0 && i + 1 < s.length()) {
            char c1 = s[i - 1], c2 = s[i + 1];
            if (c1 > c2) swap(c1, c2);
            s.erase(i - 1, 3);
            size_t j = i - 1;
            for (char ch = c1; ch <= c2; ch++) {
              s.insert(i - 1, 1, ch);
              j++;
            }
            i = j;
          } else
            ++i;
        }
        a.push_back("[" + s + "]");
      } else {
        a.push_back(string(1, str[0]));
        str.erase(0, 1);
      }
    }
  } else {
    for (size_t i = 0; i < str.length(); ++i) a.push_back(string(1, str[i]));
  }
}

void input() {
  string line;
  getline(cin, line);
  bool cur = false;
  for (size_t i = 0; i < line.length(); ++i) {
    inq[i] = cur;
    // cerr << (inq[i] ? 1 : 0);
    if (line[i] == (char)39) {
      cur = !cur;
    }
  }
  // cerr << endl;
  string str_a, str_b;
  size_t j = 0;
  while (true) {
    j = line.find(" like ", j + 1);
    // cerr << "j = " << j << endl;
    assert(j != string::npos);
    bool all_false = true;
    for (int k = 0; k < 6; k++) {
      if (inq[j + k] == true) {
        all_false = false;
        break;
      }
    }
    if (all_false) {
      str_a = line.substr(0, j);
      str_b = line.substr(j + 6);
      break;
    }
  }
  while (str_a.length() > 0 && isspace(str_a[0])) str_a.erase(0, 1);
  while (str_a.length() > 0 && isspace(str_a[str_a.length() - 1]))
    str_a.erase(str_a.length() - 1);
  while (str_b.length() > 0 && isspace(str_b[0])) str_b.erase(0, 1);
  while (str_b.length() > 0 && isspace(str_b[str_b.length() - 1]))
    str_b.erase(str_b.length() - 1);

  parse(str_a, a, false);
  parse(str_b, b, true);
#if 0
	for (size_t i = 0; i < a.size(); ++i)
		cout << a[i] << endl;
	cout << "---------\n";
	for (size_t i = 0; i < b.size(); ++i)
		cout << b[i] << endl;
#endif
}

void solve() {
  memset(c, 0, sizeof c);
  m = a.size();
  n = b.size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        c[i][j] = true;
        continue;
      }
      if (i > 0 && j == 0) {
        c[i][j] = false;
        continue;
      }
      if (i == 0 && j > 0) {
        if (b[j] == "%")
          c[i][j] = c[i][j - 1];
        else
          c[i][j] = false;
        continue;
      }
      if (b[j] == "%") {
        c[i][j] = c[i - 1][j] || c[i][j - 1];
      } else if (b[j] == "_") {
        c[i][j] = c[i - 1][j - 1];
      } else if (b[j].length() == 1) {
        if (a[i] == b[j]) {
          c[i][j] = c[i - 1][j - 1];
        } else {
          c[i][j] = false;
        }
      } else {
        assert(b[j].length() >= 3);
        assert(b[j][0] == '[');
        assert(b[j][b[j].length() - 1] == ']');
        string s = b[j].substr(1, b[j].length() - 2);
        bool negative = false;
        if (s[0] == '^') {
          s = s.substr(1);
          negative = true;
        }
        bool match = (s.find(a[i]) != string::npos);
        if (negative) match = !match;
        if (!match) {
          c[i][j] = false;
        } else {
          c[i][j] = c[i - 1][j - 1];
        }
      }
    }
  }
}

void output() {
  if (c[m - 1][n - 1])
    cout << "YES\n";
  else
    cout << "NO\n";
}

int main() {
  string line;
  getline(cin, line);
  T = atoi(line.c_str());
  for (I = 0; I < T; ++I) {
    input();
    solve();
    output();
  }
  return 0;
}

/**
 * exponent may be very large
 * 12.e+10  the dot cannot be the last character of the integral part
 * 12.e+0000000000000000000000000000001
 */

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

const int MAX_N = 1024;

string a;
int n;
int p;  // parse_int
bool ans;
// parse_dec
char sign;
int dot;
int b[MAX_N];

bool input() {
  getline(cin, a);
  if (a == "#") return false;
  string line;
  getline(cin, line);
  istringstream strin(line);
  strin >> n;
  return true;
}

bool parse_int(string a, int &p) {
  if (a.length() == 0) return false;
  int n_digits = 0;
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] == '.' || a[i] == 'e' || a[i] == 'E') return false;
    if (a[i] == '+' || a[i] == '-') {
      if (i != 0) return false;
    }
    if (a[i] >= '0' && a[i] <= '9') n_digits++;
  }
  if (n_digits <= 0) return false;
  bool negative = false;
  if (a[0] == '+' || a[0] == '-') {
    negative = (a[0] == '-');
    a.erase(0, 1);
  }
  while (a.length() > 1 && a[0] == '0') a.erase(0, 1);
  if (a.length() > 9) {
    p = 1000000000;
  } else {
    istringstream strin(a);
    strin >> p;
  }
  if (negative) p = -p;
  return true;
}

bool parse_dec(string a) {
  if (a.length() == 0) return false;
  int n_dots = 0, n_digits = 0;
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] == '.') n_dots++;
    if (a[i] == 'e' || a[i] == 'E') return false;
    if (a[i] == '+' || a[i] == '-') {
      if (i != 0) return false;
    }
    if (a[i] >= '0' && a[i] <= '9') n_digits++;
  }
  if (n_dots > 1) return false;
  if (n_digits <= 0) return false;
  if (a[0] == '+' || a[0] == '-') {
    sign = a[0];
    a.erase(0, 1);
  } else
    sign = '+';
  memset(b, 0, sizeof b);
  int m = 0;
  dot = -1;
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] >= '0' && a[i] <= '9') {
      b[m] = a[i] - '0';
      m++;
    } else if (a[i] == '.') {
      dot = m;
      if (i + 1 == a.length()) return false;
    }
  }
  if (dot == -1) dot = m;
  return true;
}

void solve() {
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] == 'e' || a[i] == 'E' || a[i] == '+' || a[i] == '-' ||
        (a[i] >= '0' && a[i] <= '9') || a[i] == '.')
      continue;
    ans = false;
    return;
  }
  size_t i = 0;
  while (i < a.length() && a[i] != 'e' && a[i] != 'E') i++;
  if (i >= a.length()) {
    p = 0;
    if (!parse_dec(a)) {
      ans = false;
      return;
    }
  } else {
    if (!parse_dec(a.substr(0, i))) {
      ans = false;
      return;
    }
    if (!parse_int(a.substr(i + 1), p)) {
      ans = false;
      return;
    }
  }
  ans = true;
}

void output() {
  if (!ans) {
    printf("Not a floating point number\n");
    return;
  }
  dot += p;
#if 0
	cerr << sign << endl;
	for (int i = 0; i < 30; i++)
		cerr << b[i];
	cerr << endl;
	cerr << "dot = " << dot << endl;
#endif
  string integral, fractional;
  if (dot <= 0) {
    integral += "0";
    for (int i = 0; i < abs(dot); i++) {
      if ((int)fractional.size() >= MAX_N) break;
      fractional += "0";
    }
    for (int i = 0; i < MAX_N; i++) {
      fractional += '0' + b[i];
    }
  } else {
    for (int i = 0; i < dot; i++) {
      if ((int)integral.size() >= MAX_N) break;
      integral += '0' + (i < MAX_N ? b[i] : '0');
    }
    for (int i = dot; i < MAX_N; i++) fractional += '0' + b[i];
  }
  while (integral.length() > 1 && integral[0] == '0') integral.erase(0, 1);
  string out;
  if (n == 0)
    out = integral;
  else {
    out = integral + ".";
    for (int i = 0; i < n; i++) {
      if (i < (int)fractional.size())
        out += fractional[i];
      else
        out += "0";
    }
  }
  if (sign == '-') {
    bool zero = true;
    for (size_t i = 0; i < out.length(); i++) {
      if (out[i] >= '1' && out[i] <= '9') {
        zero = false;
        break;
      }
    }
    if (!zero) out = '-' + out;
  }
  cout << out << endl;
}

int main() {
  while (input()) {
    solve();
    output();
  }
  return 0;
}

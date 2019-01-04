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

int main() {
  string line;
  getline(cin, line);
  istringstream strin(line);
  int n;
  strin >> n;
  int a = 0, b = 0, c = 0;
  for (int i = 0; i < n; i++) {
    getline(cin, line);
    if (line[0] == 'E')
      a++;
    else if (line[0] == 'L')
      b++;
    else
      c++;
  }
  if (a > b && a > c)
    cout << "Emperor Penguin\n";
  else if (b > a && b > c)
    cout << "Little Penguin\n";
  else
    cout << "Macaroni Penguin\n";
  return 0;
}

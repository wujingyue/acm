#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long double Real;

const Real o = 1e-8;
const Real pi = acos(-1.0);
const int max_n = 128;

typedef pair<string, string> StrPair;

vector<StrPair> questions;
vector<vector<StrPair> > answers;
vector<string> results;
string survey_name;
bool first;
int a[max_n][max_n], b[max_n][max_n], c[max_n][max_n];
int stack[max_n];

StrPair parse_pair(const string &line) {
  istringstream iss(line);
  string first, second;
  iss >> first;
  iss >> ws;
  getline(iss, second);
  return make_pair(first, second);
}

void input() {
  getline(cin, survey_name);
  string line;
  getline(cin, line);
  while (line != "#") {
    questions.push_back(parse_pair(line));
    answers.push_back(vector<StrPair>());
    getline(cin, line);
    while (line[0] == ' ') {
      answers.back().push_back(parse_pair(line));
      getline(cin, line);
    }
  }
  assert(questions.size() == answers.size());
#if 0
	cerr << "survey: " << survey_name << endl;
	for (size_t i = 0; i < questions.size(); ++i) {
		cerr << questions[i].first << ' ' << questions[i].second << endl;
		for (size_t j = 0; j < answers[i].size(); ++j) {
			cerr << "answer: " << answers[i][j].first << ' '
				<< answers[i][j].second << endl;
		}
	}
#endif

  results.clear();
  getline(cin, line);
  while (line != "#") {
    results.push_back(line);
    getline(cin, line);
  }
}

size_t find_question(const string &code) {
  for (size_t i = 0; i < questions.size(); ++i) {
    if (questions[i].first == code) return i;
  }
  assert(false);
}

void print_question(size_t i) {
  cout << questions[i].first << ' ' << questions[i].second << endl;
  for (size_t j = 0; j < answers[i].size(); ++j) {
    cout << ' ' << answers[i][j].first << ' ' << answers[i][j].second << endl;
  }
}

size_t find_answer(size_t i, const string &code) {
  for (size_t j = 0; j < answers[i].size(); ++j) {
    if (answers[i][j].first == code) return j;
  }
  assert(false);
}

void print_6(const string &a) {
  for (size_t i = 0; i + a.length() < 6; ++i) cout << ' ';
  cout << a;
}

void print_6(int a) {
  ostringstream oss;
  oss << a;
  print_6(oss.str());
}

bool search(int i, int sum, pair<int, int> *range, int n) {
  if (i >= n) {
    if (sum == 100)
      return true;
    else
      return false;
  }
  for (stack[i] = range[i].first; stack[i] <= range[i].second; ++stack[i]) {
    if (search(i + 1, sum + stack[i], range, n)) return true;
  }
  return false;
}

int Floor(int a, int b) { return a * 100 / b; }

int Ceil(int a, int b) { return (a * 100 + b - 1) / b; }

// results => b
void calc_percent_x(int m, int n) {
  for (int x = 0; x <= m; x++) {
    if (a[x][n] == 0) {
      for (int y = 0; y <= n; ++y) b[x][y] = -1;
      continue;
    }
    pair<int, int> range[max_n];
    for (int y = 0; y < n; y++) {
      range[y].first = Floor(a[x][y], a[x][n]);
      range[y].second = Ceil(a[x][y], a[x][n]);
    }
    bool ret = search(0, 0, range, n);
    assert(ret);
    for (int y = 0; y < n; y++) b[x][y] = stack[y];
    b[x][n] = 100;
  }
}

// results => c
void calc_percent_y(int m, int n) {
  for (int y = 0; y <= n; y++) {
    if (a[m][y] == 0) {
      for (int x = 0; x <= m; ++x) c[x][y] = -1;
      continue;
    }
    pair<int, int> range[max_n];
    for (int x = 0; x < m; x++) {
      range[x].first = Floor(a[x][y], a[m][y]);
      range[x].second = Ceil(a[x][y], a[m][y]);
    }
    bool ret = search(0, 0, range, m);
    assert(ret);
    for (int x = 0; x < m; x++) c[x][y] = stack[x];
    c[m][y] = 100;
  }
}

void print_percent_6(int a) {
  if (a < 0)
    print_6("-");
  else {
    ostringstream oss;
    oss << a;
    for (size_t i = 0; i + oss.str().length() < 5; ++i) cout << ' ';
    cout << oss.str() << "%";
  }
}

void print_sheet(const string &sheet_name, const string &code1,
                 const string &code2) {
  if (first)
    first = false;
  else
    cout << endl;
  cout << survey_name << " - " << sheet_name << endl;
  size_t i1 = find_question(code1);
  size_t i2 = find_question(code2);
  print_question(i1);
  print_question(i2);

  memset(a, 0, sizeof a);
  for (size_t k = 0; k < results.size(); ++k) {
    size_t j1 = find_answer(i1, string(1, results[k][i1]));
    size_t j2 = find_answer(i2, string(1, results[k][i2]));
    a[j1][j2]++;
  }
  for (size_t x = 0; x < answers[i1].size(); ++x) {
    for (size_t y = 0; y < answers[i2].size(); ++y)
      a[x][answers[i2].size()] += a[x][y];
  }
  for (size_t y = 0; y < answers[i2].size(); ++y) {
    for (size_t x = 0; x < answers[i1].size(); ++x)
      a[answers[i1].size()][y] += a[x][y];
  }
  for (size_t x = 0; x < answers[i1].size(); ++x) {
    for (size_t y = 0; y < answers[i2].size(); ++y)
      a[answers[i1].size()][answers[i2].size()] += a[x][y];
  }

  calc_percent_x(answers[i1].size(), answers[i2].size());
  calc_percent_y(answers[i1].size(), answers[i2].size());

  cout << endl;
  print_6("");
  for (size_t j2 = 0; j2 < answers[i2].size(); ++j2)
    print_6(questions[i2].first + ":" + answers[i2][j2].first);
  print_6("TOTAL");
  cout << endl;
  for (size_t x = 0; x < answers[i1].size(); ++x) {
    print_6(questions[i1].first + ":" + answers[i1][x].first);
    for (size_t y = 0; y <= answers[i2].size(); ++y) print_6(a[x][y]);
    cout << endl;
    // percent x
    print_6("");
    for (size_t y = 0; y <= answers[i2].size(); ++y) print_percent_6(b[x][y]);
    cout << endl;
    // percent y
    print_6("");
    for (size_t y = 0; y <= answers[i2].size(); ++y) print_percent_6(c[x][y]);
    cout << endl;
  }
  print_6("TOTAL");
  for (size_t y = 0; y <= answers[i2].size(); ++y)
    print_6(a[answers[i1].size()][y]);
  cout << endl;
  print_6("");
  for (size_t y = 0; y <= answers[i2].size(); ++y)
    print_percent_6(b[answers[i1].size()][y]);
  cout << endl;
  print_6("");
  for (size_t y = 0; y <= answers[i2].size(); ++y)
    print_percent_6(c[answers[i1].size()][y]);
  cout << endl;
}

void solve() {
  first = true;
  string code1;
  cin >> code1;
  while (code1 != "#") {
    string code2, sheet_name;
    cin >> code2;
    cin >> ws;
    getline(cin, sheet_name);
    print_sheet(sheet_name, code1, code2);
    cin >> code1;
  }
}

void output() {}

int main() {
  input();
  solve();
  output();
  return 0;
}

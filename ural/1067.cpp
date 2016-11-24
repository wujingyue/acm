#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <cctype>
using namespace std;

const int MAX_N = 512;

struct Path {
	vector<string> dirs;
	bool operator<(const Path &b) const {
		for (size_t i = 0; i < min(dirs.size(), b.dirs.size()); i++) {
			if (dirs[i] < b.dirs[i])
				return true;
			if (dirs[i] > b.dirs[i])
				return false;
		}
		return dirs.size() < b.dirs.size();
	}
};

Path a[MAX_N];
int n;

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string line;
		cin >> line;
		a[i].dirs.clear();
		size_t j1 = 0;
		assert(line[0] != '\\');
		for (size_t j2 = 1; j2 < line.length(); j2++) {
			if (line[j2] == '\\') {
				a[i].dirs.push_back(line.substr(j1, j2 - j1));
				j1 = j2 + 1;
			}
		}
		assert(j1 < line.length());
		a[i].dirs.push_back(line.substr(j1));
	}
}

void solve() {
	sort(a, a + n);
}

void print_spaces(int k) {
	for (int i = 0; i < k; i++)
		printf(" ");
}

void print(int i1, int i2, int j) {
	for (int s = i1; s <= i2;) {
		int e = s + 1;
		while (e <= i2 && a[e].dirs[j] == a[s].dirs[j])
			e++;
		print_spaces(j);
		printf("%s\n", a[s].dirs[j].c_str());
		while (s < e && (int)a[s].dirs.size() <= j + 1)
			s++;
		if (s < e)
			print(s, e - 1, j + 1);
		s = e;
	}
}

void output() {
#if 0
	for (int i = 0; i < n; i++) {
		for (size_t j = 0; j < a[i].dirs.size(); j++)
			cerr << a[i].dirs[j] << ' ';
		cerr << endl;
	}
#endif
	print(0, n - 1, 0);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


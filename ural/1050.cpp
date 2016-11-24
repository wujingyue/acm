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

string a;
int change[1024 * 1024];
vector<int> seps;

void input() {
	a.clear();
	string line;
	while (getline(cin, line)) {
		a += line;
		a += '\n';
	}
}

void find_all(const string &b) {
	size_t i = 0;
	while (true) {
		size_t j = a.find(b, i);
		if (j == string::npos)
			break;
		// cerr << j << endl;
		seps.push_back(j);
		i = j + 1;
	}
}

void latex(int i, int j) {
	// cerr << i << ' ' << j << endl;
	int cur = 1;
	for (int k = i; k < j; k++) {
		if (a[k] == '"' && (k == i || a[k - 1] != '\\')) {
			change[k] = cur;
			cur = -cur;
		}
	}
	int k = j - 1;
	while (k >= i && change[k] == 0)
		k--;
	if (k >= i && change[k] == 1)
		change[k] = -2;
}

void solve() {
	seps.clear();
	find_all("\\par");
	find_all("\n\n");
	find_all("\\endinput");
	seps.push_back(0);
	sort(seps.begin(), seps.end());
	seps.resize(unique(seps.begin(), seps.end()) - seps.begin());
	memset(change, 0, sizeof change);
	for (size_t k = 1; k < seps.size(); k++) {
		latex(seps[k - 1], seps[k]);
	}
}

void output() {
	for (size_t i = 0; i < a.length(); i++) {
		if (change[i] == 0) {
			if (a[i] == '\n')
				cout << endl;
			else
				cout << a[i];
		} else if (change[i] == 1)
			cout << "``";
		else if (change[i] == -1) 
			cout << "''";
	}
}

int main() {
	input();
	solve();
	output();
	return 0;
}


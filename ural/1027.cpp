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

string a, b;
bool comment[65536];
bool ans;

void input() {
	a.clear();
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\r')
			continue;
		a += (char)c;
	}
}

void solve() {
	memset(comment, 0, sizeof comment);
	for (size_t i = 0; i + 1 < a.length();) {
		if (a[i] == '(' && a[i + 1] == '*') {
			// comments
			size_t j = i + 2;
			while (j + 1 < a.length() && !(a[j] == '*' && a[j + 1] == ')'))
				j++;
			if (j + 1 >= a.length()) {
				// cerr << 1 << endl;
				ans = false;
				return;
			}
			for (size_t k = i; k < j + 2; k++)
				comment[k] = true;
			i = j + 2;
		} else {
			i++;
		}
	}
	b.clear();
	for (size_t i = 0; i < a.length(); i++) {
		if (!comment[i])
			b += a[i];
	}
	for (size_t i = 0; i < b.length();) {
		if (b[i] == '(') {
			// expression
			int level = 1;
			size_t j = i + 1;
			while (j < b.length() && level > 0) {
				if (b[j] == '(')
					level++;
				else if (b[j] == ')')
					level--;
				j++;
			}
			assert(level >= 0);
			if (level > 0) {
				// cerr << 2 << endl;
				ans = false;
				return;
			}
			for (size_t k = i; k < j; k++) {
				if (b[k] == '=' || b[k] == '+' || b[k] == '-' || b[k] == '*' || b[k] == '/'
						|| b[k] == ')' || b[k] == '(' || (b[k] >= '0' && b[k] <= '9'))
					continue;
				// cerr << 3 << ' ' << b.substr(i, j - i) << endl;
				ans = false;
				return;
			}
			i = j;
		} else if (b[i] == ')') {
			// cerr << 4 << endl;
			ans = false;
			return;
		} else {
			i++;
		}
	}
	ans = true;
}

void output() {
	if (ans)
		printf("YES\n");
	else
		printf("NO\n");
}

int main() {
	input();
	solve();
	output();
	return 0;
}


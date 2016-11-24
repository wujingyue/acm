/**
 * p[max_m]
 * typo: c.y = a.y + c.y
 */

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

typedef long double Real;

const int max_n = 16384;
const int max_m = max_n * 2;
const Real o = 1e-8;
const Real PI = acos(-1.0);

struct Point {
	int x, y;
};
Point operator-(const Point &a) {
	Point b; b.x = -a.x; b.y = -a.y;
	return b;
}
Point operator+(const Point &a, const Point &b) {
	Point c; c.x = a.x + b.x; c.y = a.y + b.y;
	return c;
}

Real len(const Point &a) {
	return sqrt((Real)a.x * a.x + (Real)a.y * a.y);
}
bool is_zero(const Point &a) {
	return a.x == 0 && a.y == 0;
}

Point p[max_m];
int n, L;
int m;
vector<int> zone[3];
vector<int> c[max_m];
int w[max_m];
int ans;
int s[max_m];

void input() {
	cin >> n >> L;
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
}

int get_zone(const Point &a) {
	if (is_zero(a))
		return 0;
	Real t = atan2((Real)a.y, (Real)a.x);
	int j;
	if (t <= -PI * 2 / 3)
		j = 0;
	else if (t <= -PI / 3)
		j = 1;
	else if (t <= 0)
		j = 2;
	else if (t <= PI / 3)
		j = 0;
	else if (t <= PI * 2 / 3)
		j = 1;
	else
		j = 2;
	return j;
}

bool can_merge(const Point &a, const Point &b) {
	if (is_zero(a) || is_zero(b))
		return true;
	Point c = a + b;
	return (long long)c.x * c.x + (long long)c.y * c.y <=
		(long long)a.x * a.x + (long long)a.y * a.y +
		(long long)b.x * b.x + (long long)b.y * b.y;
}

bool can_merge_precise(const Point &a, const Point &b) {
	if (is_zero(a) || is_zero(b))
		return true;
	Real lc = len(a + b), la = len(a), lb = len(b);
	return lc * lc - la * la - lb * lb <= -la * lb + o;
}

void add_child(int x, int y) {
	assert(y < x);
	c[x].push_back(y);
}

void solve() {
	for (int i = 0; i < 3; i++)
		zone[i].clear();
	for (int i = 0; i < n; i++) {
		zone[get_zone(p[i])].push_back(i);
	}
	m = n;
	for (int i = 0; i < max_m; i++)
		c[i].clear();
	while (true) {
		int j = 0;
		while (j < 3 && zone[j].size() < 2)
			j++;
		if (j == 3)
			break;
		int i1, i2;
		i1 = zone[j].back(); zone[j].pop_back();
		i2 = zone[j].back(); zone[j].pop_back();
		if (!can_merge(p[i1], p[i2])) {
			w[i1] = 1; w[i2] = -1;
			p[i2] = -p[i2];
			assert(can_merge(p[i1], p[i2]));
		} else {
			w[i1] = 1; w[i2] = 1;
		}
		p[m] = p[i1] + p[i2];
		// cerr << i1 << ' ' << i2 << ' ' << m << endl;
		assert(i1 < m); assert(i2 < m);
		add_child(m, i1); add_child(m, i2);
		zone[get_zone(p[m])].push_back(m);
		m++;
	}
	vector<int> rest;
	for (int j = 0; j < 3; j++) {
		if (!zone[j].empty()) {
			assert(zone[j].size() == 1);
			rest.push_back(zone[j].back());
		}
	}
	assert(rest.size() <= 3);
	if (rest.size() == 1) {
		ans = rest.back();
		return;
	}
	if (rest.size() > 2) {
		bool found = false;
		for (int i1 = 0; i1 < 3; i1++) {
			for (int i2 = i1 + 1; i2 < 3; i2++) {
				if (can_merge_precise(p[rest[i1]], p[rest[i2]])) {
					w[rest[i1]] = w[rest[i2]] = 1;
					assert(rest[i1] < m); assert(rest[i2] < m);
					add_child(m, rest[i1]); add_child(m, rest[i2]);
					p[m] = p[rest[i1]] + p[rest[i2]];
					rest.erase(rest.begin() + i2);
					rest.erase(rest.begin() + i1);
					rest.push_back(m);
					m++;
					found = true;
					break;
				}
				if (can_merge_precise(p[rest[i1]], -p[rest[i2]])) {
					w[rest[i1]] = 1; w[rest[i2]] = -1;
					assert(rest[i1] < m); assert(rest[i2] < m);
					add_child(m, rest[i1]); add_child(m, rest[i2]);
					p[rest[i2]] = -p[rest[i2]];
					p[m] = p[rest[i1]] + p[rest[i2]];
					rest.erase(rest.begin() + i2);
					rest.erase(rest.begin() + i1);
					rest.push_back(m);
					m++;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		assert(rest.size() == 2);
	}
	assert(rest.size() == 2);
	assert(rest[0] < m); assert(rest[1] < m);
	add_child(m, rest[0]); add_child(m, rest[1]);
	w[rest[0]] = w[rest[1]] = 1;
	if (!can_merge(p[rest[0]], p[rest[1]])) {
		p[rest[1]] = -p[rest[1]];
		w[rest[1]] = -1;
	}
	p[m] = p[rest[0]] + p[rest[1]];
	m++;
	ans = m - 1;
}

void mark_sign(int x, int sign) {
	// cerr << x << endl;
	if (c[x].size() == 0) {
		s[x] = sign;
		return;
	}
	assert(c[x].size() == 2);
	mark_sign(c[x][0], sign * w[c[x][0]]);
	mark_sign(c[x][1], sign * w[c[x][1]]);
}

void output() {
	// cerr << "ans = " << ans << endl;
	mark_sign(ans, 1);
	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		if (s[i] == 1)
			cout << "+";
		else
			cout << "-";
	}
	cout << endl;
}

int main() {
	input();
	solve();
	output();
	return 0;
}


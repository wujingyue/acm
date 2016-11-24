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

const int max_n = 256;
const Real o = 1e-8;

struct Point {
	Real x, y;
};
Point operator-(const Point &a, const Point &b) {
	Point c; c.x = a.x - b.x; c.y = a.y - b.y;
	return c;
}

inline Real dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline Real cross(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

bool prev(const Point &a, const Point &b, const Point &c) {
	Real mul = cross(a - c, b - c);
	return mul > o || (mul >= -o && dist(a, c) < dist(b, c));
}

struct Compare {
	Point c;
	Compare(const Point &cc): c(cc) {}
	bool operator()(const Point &a, const Point &b) {
		return prev(a, b, c);
	}
};

vector<Point> p;
int n;
Real c[max_n][max_n][2];
Real ans;

void input() {
	cin >> n;
	p.clear();
	for (int i = 0; i < n; i++) {
		Point a;
		cin >> a.x >> a.y;
		p.push_back(a);
	}
}

Real dp() {
	for (int i = 1; i < n; i++) {
		c[i][i][0] = 0;
		c[i][i][1] = 0;
	}
	for (int s = 1; s < n - 1; s++) {
		for (int i = 1; i + s < n; i++) {
			int j = i + s;
			c[i][j][0] = min(c[i + 1][j][0] + dist(p[i], p[i + 1]), c[i + 1][j][1] + dist(p[i], p[j]));
			c[i][j][1] = min(c[i][j - 1][1] + dist(p[j], p[j - 1]), c[i][j - 1][0] + dist(p[i], p[j]));
		}
	}
	return min(c[1][n - 1][0] + dist(p[0], p[1]), c[1][n - 1][1] + dist(p[0], p[n - 1]));
}

void solve() {
	for (int i = 1; i < n; i++) {
		if (p[i].y < p[0].y - o || (p[i].y <= p[0].y + o && p[i].x < p[0].x))
			swap(p[0], p[i]);
	}
	sort(p.begin() + 1, p.end(), Compare(p[0]));
	ans = 1e+20;
	for (int i = 0; i < n; i++) {
		ans = min(ans, dp());
		Point a = p.front();
		p.erase(p.begin());
		p.push_back(a);
	}
}

void output() {
	printf("%.3Lf\n", ans);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


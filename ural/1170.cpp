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

const Real o = 1e-8;
const Real pi = acos(-1.0);
const Real oo = 1e+20;

const int max_n = 1024;

struct Rect {
	Real x1, y1, x2, y2, c;
};

Rect r[max_n];
int n;
Real L, c0;
Real ans, ans_x, ans_y;

void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%Lf %Lf %Lf %Lf %Lf", &r[i].x1, &r[i].y1, &r[i].x2, &r[i].y2, &r[i].c);
	}
	scanf("%Lf %Lf", &c0, &L);
}

bool by_sum(const pair<Real, Real> &a, const pair<Real, Real> &b) {
	return a.first + a.second < b.first + b.second;
}

Real dist(Real x1, Real y1, Real x2, Real y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

Real cross(Real x1, Real y1, Real x2, Real y2) {
	return x1 * y2 - x2 * y1;
}

bool get_inter(Real x1, Real y1, Real x2, Real y2, Real x3, Real y3, Real x4, Real y4, Real &x, Real &y) {
	if (cross(x3, y3, x2, y2) * cross(x4, y4, x2, y2) <= o) {
		if (abs(x3 - x4) <= o && abs(y3 - y4) <= o) {
			x = x3; y = y3;
			return true;
		}
		Real a1, b1, c1, a2, b2, c2;
		a1 = y3 - y4; b1 = x4 - x3; c1 = cross(x3, y3, x4, y4);
		a2 = y1 - y2; b2 = x2 - x1; c2 = cross(x1, y1, x2, y2);
		x = cross(b1, c1, b2, c2) / cross(a1, b1, a2, b2);
		y = cross(c1, a1, c2, a2) / cross(a1, b1, a2, b2);
		return true;
	}
	return false;
}

Real get_time(Real x0, Real y0) {
	// cerr << x0 << ' ' << y0 << endl;
	Real d = L, res = 0;
	for (int i = 0; i < n; i++) {
		vector<pair<Real, Real> > inters;
		Real x, y;
		if (get_inter(0, 0, x0, y0, r[i].x1, r[i].y1, r[i].x1, r[i].y2, x, y))
			inters.push_back(make_pair(x, y));
		if (get_inter(0, 0, x0, y0, r[i].x1, r[i].y2, r[i].x2, r[i].y2, x, y))
			inters.push_back(make_pair(x, y));
		if (get_inter(0, 0, x0, y0, r[i].x2, r[i].y2, r[i].x2, r[i].y1, x, y))
			inters.push_back(make_pair(x, y));
		if (get_inter(0, 0, x0, y0, r[i].x2, r[i].y1, r[i].x1, r[i].y1, x, y))
			inters.push_back(make_pair(x, y));
		if (inters.empty())
			continue;
		sort(inters.begin(), inters.end(), by_sum);
		Real x1, y1, x2, y2;
		x1 = inters.front().first; y1 = inters.front().second;
		x2 = inters.back().first; y2 = inters.back().second;
		Real s = dist(x1, y1, x2, y2);
		// cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
		d -= s;
		res += s * r[i].c;
		// cerr << "add: " << s << ' ' << r[i].c << endl;
	}
	res += d * c0;
	// cerr << "add: " << d << ' ' << c0 << endl;
	// cerr << "res = " << res << endl;
	return res;
}

void test(Real x0, Real y0) {
	Real d = dist(0, 0, x0, y0);
	Real x = x0 * L / d, y = y0 * L / d;
	Real t = get_time(x, y);
	if (t < ans) {
		ans = t;
		ans_x = x; ans_y = y;
	}
}

void solve() {
	ans = oo;
	for (int i = 0; i < n; i++) {
		test(r[i].x1, r[i].y1);
		test(r[i].x1, r[i].y2);
		test(r[i].x2, r[i].y1);
		test(r[i].x2, r[i].y2);
	}
}

void output() {
	printf("%.6Lf\n%.6Lf %.6Lf\n", ans, ans_x, ans_y);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


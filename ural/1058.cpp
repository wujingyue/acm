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

const Real o = 1e-6;
const int MAX_N = 64;
const Real oo = 1e+20;

struct Point {
	Real x, y;
	Point(Real xx = 0.0, Real yy = 0.0) : x(xx), y(yy) {}
};

Point p[MAX_N];
vector<pair<Real, Real> > cand;
vector<pair<int, int> > segs;
int n;
Real ans;

inline Real sqr(Real a) {
	return a * a;
}

void my_assert(bool cond) {
	while (!cond) {
		cout << "111111111111\n";
	}
}

void print_poly(const vector<Point> &p) {
	fprintf(stderr, "-----\n");
	for (int i = 0; i < (int)p.size(); i++)
		fprintf(stderr, "%Lf %Lf\n", p[i].x, p[i].y);
	fprintf(stderr, "*****\n");
}

void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%Lf %Lf", &p[i].x, &p[i].y);
	p[n] = p[0];
}

inline Real multi(Real x1, Real y1, Real x2, Real y2) {
	return x1 * y2 - x2 * y1;
}

void get_inter(Real a1, Real b1, Real c1, Real a2, Real b2, Real c2, Real &x, Real &y) {
	x = multi(b1, c1, b2, c2) / multi(a1, b1, a2, b2);
	y = multi(c1, a1, c2, a2) / multi(a1, b1, a2, b2);
}

void get_inter2(Real a1, Real b1, Real c1, Real a2, Real b2, Real c2, Real &x, Real &y) {
	my_assert(abs(multi(a1, b1, a2, b2)) > o);
	x = multi(b1, c1, b2, c2) / multi(a1, b1, a2, b2);
	y = multi(c1, a1, c2, a2) / multi(a1, b1, a2, b2);
}

Real area(const vector<Point> &p) {
	Real res = 0;
	for (size_t i = 1; i + 1 < p.size(); i++)
		res += multi(p[i].x - p[0].x, p[i].y - p[0].y, p[i + 1].x - p[0].x, p[i + 1].y - p[0].y);
	return abs(res) / 2;
}

void solve() {
	cand.clear();
	segs.clear();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			Real a1, b1, a2, b2;
			a1 = p[i + 1].y - p[i].y; b1 = p[i].x - p[i + 1].x;
			a2 = p[j + 1].y - p[j].y; b2 = p[j].x - p[j + 1].x;
			if (a1 * a1 + b1 * b1 <= o || a2 * a2 + b2 * b2 <= o)
				continue;
			if (abs(multi(a1, b1, a2, b2)) <= o) {
				cand.push_back(make_pair(b1, -a1));
				segs.push_back(make_pair(i, j));
			} else {
				Real x1, y1, x2, y2;
				my_assert(a1 * a1 + b1 * b1 > o);
				Real k = sqrt(1000 / (a1 * a1 + b1 * b1));
				x1 = -b1 * k; y1 = a1 * k;
				my_assert(a2 * a2 + b2 * b2 > o);
				k = sqrt(1000 / (a2 * a2 + b2 * b2));
				x2 = -b2 * k; y2 = a2 * k;
				cand.push_back(make_pair((x1 + x2) / 2, (y1 + y2) / 2));
				segs.push_back(make_pair(i, j));
				x2 = -x2; y2 = -y2;
				cand.push_back(make_pair((x1 + x2) / 2, (y1 + y2) / 2));
				segs.push_back(make_pair(i, j));
			}
		}
	}
#if 0
	for (size_t i = 0; i < cand.size(); i++)
		fprintf(stderr, "%Lf %Lf\n", cand[i].first, cand[i].second);
#endif
	ans = oo;
	for (size_t k = 0; k < cand.size(); k++) {
		Real a = cand[k].first, b = cand[k].second;
		if (abs(a) <= o && abs(b) <= o)
			continue;
		Real c_min = oo, c_max = -oo;
		int i = segs[k].first, j = segs[k].second;
		Real tmp;
		tmp = a * p[i].x + b * p[i].y;
		c_min = min(c_min, tmp);
		c_max = max(c_max, tmp);
		tmp = a * p[i + 1].x + b * p[i + 1].y;
		c_min = min(c_min, tmp);
		c_max = max(c_max, tmp);
		tmp = a * p[j].x + b * p[j].y;
		c_min = min(c_min, tmp);
		c_max = max(c_max, tmp);
		tmp = a * p[j + 1].x + b * p[j + 1].y;
		c_min = min(c_min, tmp);
		c_max = max(c_max, tmp);
		// fprintf(stderr, "%Lf %Lf %Lf %Lf\n", a, b, c_min, c_max);
		Real l = c_min, h = c_max;
		bool equal = false;
		while (h - l > 1e-6) {
			Real c = (l + h) / 2;
			vector<Point> p1, p2;
			for (int i = 0; i < n; i++) {
				if (abs(p[i].x - p[i + 1].x) <= o && abs(p[i].y - p[i + 1].y) <= o)
					continue;
				Real c1 = a * p[i].x + b * p[i].y, c2 = a * p[i + 1].x + b * p[i + 1].y;
				if (c1 <= c + o)
					p1.push_back(p[i]);
				else
					p2.push_back(p[i]);
				if ((c1 <= c + o && c2 > c + o) || (c1 > c + o && c2 <= c + o)) {
					Real x, y;
					get_inter2(p[i + 1].y - p[i].y, p[i].x - p[i + 1].x, -multi(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y),
							a, b, -c, x, y);
					p1.push_back(Point(x, y));
					p2.push_back(Point(x, y));
				}
			}
#if 0
			print_poly(p1);
			print_poly(p2);
#endif
			// fprintf(stderr, "c = %Lf, p1 = %Lf, p2 = %Lf\n", c, area(p1), area(p2));
			Real diff = area(p1) - area(p2);
			if (abs(diff) <= o) {
				equal = true;
				l = c;
				h = c;
				break;
			}
			if (diff < 0)
				l = c;
			else
				h = c;
		}
		if (!equal)
			continue;
		vector<Point> inters;
		for (int i = 0; i < n; i++) {
			Real c1 = a * p[i].x + b * p[i].y, c2 = a * p[i + 1].x + b * p[i + 1].y;
			if ((c1 <= l + o && c2 > l + o) || (c1 > l + o && c2 <= l + o)) {
				Real x, y;
				get_inter2(p[i + 1].y - p[i].y, p[i].x - p[i + 1].x, -multi(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y),
						a, b, -l, x, y);
				inters.push_back(Point(x, y));
			}
		}
		// fprintf(stderr, "inters.size() = %u\n", inters.size());
		// fprintf(stderr, "%Lf %Lf %Lf\n", a, b, l);
		my_assert(inters.size() == 2);
		Real d = sqrt(sqr(inters[0].x - inters[1].x) + sqr(inters[0].y - inters[1].y));
		if (d < ans)
			ans = d;
	}
}

void output() {
	printf("%.4Lf\n", ans);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


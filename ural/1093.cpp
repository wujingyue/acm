/**
 * There may be the case that a = b = c = 0. Answer missed for such cases
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

const Real o = 1e-8;

Real cx, cy, cz, nx, ny, nz, r, sx, sy, sz, vx, vy, vz;
bool ans;

void input() {
	scanf("%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
			&cx, &cy, &cz, &nx, &ny, &nz, &r, &sx, &sy, &sz, &vx, &vy, &vz);
}

inline Real sqr(Real a) {
	return a * a;
}

bool hit_at(Real t) {
	Real mx, my, mz;
	mx = sx + vx * t;
	my = sy + vy * t;
	mz = sz + vz * t - 5 * t * t;
	return sqrt(sqr(mx - cx) + sqr(my - cy) + sqr(mz - cz)) < r - o;
}

void solve() {
	Real a = -5.0 * nz;
	Real b = vx * nx + vy * ny + vz * nz;
	Real c = (sx - cx) * nx + (sy - cy) * ny + (sz - cz) * nz;
	if (abs(a) <= o && abs(b) <= o) {
		// assert(abs(c) > o);
		ans = false;
		return;
	}
	Real t1, t2;
	if (abs(a) <= o) {
		t1 = t2 = -c / b;
	} else {
		Real d = b * b - 4 * a * c;
		if (d < -o) {
			ans = false;
			return;
		}
		if (d <= o) {
			t1 = t2 = -b / a / 2;
		} else {
			t1 = (-b + sqrt(d)) / a / 2;
			t2 = (-b - sqrt(d)) / a / 2;
		}
	}
	ans = (t1 > o && hit_at(t1)) || (t2 > o && hit_at(t2));
}

void output() {
	if (ans)
		printf("HIT\n");
	else
		printf("MISSED\n");
}

int main() {
	input();
	solve();
	output();
	return 0;
}


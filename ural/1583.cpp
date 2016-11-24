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

const int max_n = 128;

typedef long double Real;

const Real o = 1e-8;
const Real PI = acos(-1.0);

struct Ball {
	Real x, y, z, r;
};

Ball p[max_n];
int n;
vector<int> ans;

void input() {
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> p[i].x >> p[i].y >> p[i].z >> p[i].r;
}

inline Real sqr(Real a) {
	return a * a;
}

inline Real cubic(Real a) {
	return a * a * a;
}

Real get_v(Real y) {
	Real ans = y * 100;
	for (int i = 0; i < n; i++) {
		if (y <= p[i].y - p[i].r + o)
			continue;
		if (p[i].y + p[i].r <= y + o) {
			ans -= 4 * PI * cubic(p[i].r) / 3;
			continue;
		}
		Real h = p[i].y - y;
		ans -= PI * (2 * cubic(p[i].r) / 3 + cubic(h) / 3 - sqr(p[i].r) * h);
	}
	return ans;
}

Real get_y(Real y0) {
	Real low = 0, high = 101;
	while (high - low > o) {
		Real mid = (low + high) / 2;
		if (get_v(mid) - get_v(y0) < 500)
			low = mid;
		else
			high = mid;
	}
	return (low + high) / 2;
}

void solve() {
	ans.clear();
	while (true) {
		Real y = get_y(ans.empty() ? 0 : (Real)ans.back() / 10000);
		int int_y = (int)(y * 10000 + 0.5);
		if (int_y >= 1000000)
			break;
		ans.push_back(int_y);
	}
}

void output() {
	printf("%u\n", ans.size());
	for (size_t i = 0; i < ans.size(); ++i)
		printf("%d\n", ans[i]);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


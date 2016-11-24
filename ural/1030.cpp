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

const Real R = 6875.0 / 2;
const Real o = 1e-6;
const Real PI = acos(-1.0);

inline Real sqr(Real a) {
	return a * a;
}

void extract(const string &line1, const string &line2, Real &x, Real &y, Real &z) {
	Real al, th;
	int h, m, s;
	char ch;
	string token;
	istringstream strin;
	strin.clear(); strin.str(line1);
	strin >> h >> ch >> m >> ch >> s >> ch >> token;
	// cerr << token << endl;
	th = h * PI / 180 + m * PI / 60 / 180 + s * PI / 3600 / 180;
	if (token == "SL")
		th = -th;
	strin.clear(); strin.str(line2);
	strin >> token >> h >> ch >> m >> ch >> s >> ch >> token;
	// cerr << token << endl;
	al = h * PI / 180 + m * PI / 60 / 180 + s * PI / 3600 / 180;
	if (token == "WL.")
		al = -al;
	z = R * sin(th);
	x = R * cos(th) * cos(al);
	y = R * cos(th) * sin(al);
	// cerr << x << ' ' << y << ' ' << z << endl;
}

int main() {
	Real x1, y1, z1, x2, y2, z2;
	string line, line1, line2;
	getline(cin, line);
	getline(cin, line);
	getline(cin, line);
	getline(cin, line1);
	getline(cin, line2);
	extract(line1, line2, x1, y1, z1);
	getline(cin, line);
	getline(cin, line1);
	getline(cin, line2);
	extract(line1, line2, x2, y2, z2);
	Real d = sqrt(sqr(x1 - x2) + sqr(y1 - y2) + sqr(z1 - z2));
	// cerr << d << endl;
	Real th = acos(1 - d * d / 2 / R / R);
	Real len = th * R;
	len = abs(len);
	len = (int)(len * 100 + 0.5) / 100.0;
	printf("The distance to the iceberg: %.2Lf miles.\n", len);
	if (len < 100 - o)
		printf("DANGER!\n");
	return 0;
}


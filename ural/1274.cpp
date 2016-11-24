/**
 * use long long
 * make sure the denominator is still > 0 after /
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

struct Frac {
	int sign;
	long long a, b, c;
};

Frac a, b, c;
char op;

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

long long my_abs(long long a) {
	return a < 0 ? -a : a;
}

void read_frac(Frac &a) {
	string line;
	getline(cin, line);
	if (line.find("/") == string::npos) {
		istringstream strin(line);
		strin >> a.a;
		a.sign = (a.a < 0 ? -1 : 1);
		a.a = my_abs(a.a);
		a.b = 0; a.c = 1;
	} else {
		istringstream strin(line);
		char ch;
		if (line.find("-") == string::npos)
			a.sign = 1;
		else {
			strin >> ch;
			assert(ch == '-');
			a.sign = -1;
		}
		a.a = 0;
		if (line.find(" ") != string::npos)
			strin >> a.a;
		strin >> a.b >> ch >> a.c;
		assert(ch == '/');
	}
	assert(a.a >= 0);
}

void read_op(char &op) {
	string line;
	getline(cin, line);
	istringstream strin(line);
	strin >> op;
}

void normalize(Frac &a) {
	a.b = a.a * a.c + a.b;
	if (a.sign == -1) {
		a.sign = 1;
		a.b = -a.b;
	}
	a.a = 0;
	assert(a.sign == 1);
}

void reduce(Frac &a) {
	long long g = gcd(my_abs(a.b), my_abs(a.c));
	a.b /= g;
	a.c /= g;
}

Frac compute(char op, const Frac &a, const Frac &b) {
	Frac c;
	if (op == '+' || op == '-') {
		c.c = a.c * b.c / gcd(a.c, b.c);
		if (op == '+')
			c.b = a.b * (c.c / a.c) + b.b * (c.c / b.c);
		else
			c.b = a.b * (c.c / a.c) - b.b * (c.c / b.c);
	} else if (op == '*') {
		c.b = a.b * b.b;
		c.c = a.c * b.c;
	} else {
		c.b = a.b * b.c;
		c.c = a.c * b.b;
		if (c.c < 0) {
			c.b = -c.b;
			c.c = -c.c;
		}
	}
	c.a = 0;
	c.sign = 1;
	reduce(c);
	return c;
}

void print(Frac &a) {
	if (a.b < 0) {
		a.sign = -1;
		a.b = -a.b;
	}
	a.a = a.b / a.c;
	a.b %= a.c;
	assert(a.a >= 0 && a.b >= 0 && a.c > 0);
	if (a.a == 0 && a.b == 0) {
		cout << 0 << endl;
		return;
	}
	if (a.sign == -1)
		cout << '-';
	if (a.a > 0)
		cout << a.a;
	if (a.b > 0) {
		if (a.a > 0)
			cout << ' ';
		cout << a.b << '/' << a.c;
	}
	cout << endl;
}

void input() {
	read_frac(a);
	read_op(op);
	read_frac(b);
}

void solve() {
	normalize(a);
	normalize(b);
	reduce(a); reduce(b);
	// printf("%lld / %lld\n", a.b, a.c);
	// printf("%lld / %lld\n", b.b, b.c);
	c = compute(op, a, b);
}

void output() {
	print(c);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


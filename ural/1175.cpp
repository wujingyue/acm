/*
 * Step 1: (a1, a2) advances one step each time. (b1, b2) advances two steps each time. 
 * Step 2: q = j - i. q is valid but may not be minimum.
 * Step 3: Starting from (x_q, x_{q + 1}), look for a loop. The length of the loop is the minimum q. 
 * Step 4: (a1, a2) = (x1, x2), (b1, b2) = (x_{q + 1}, x_{q + 2}). 
 * 	   Both of them advance one step each time until they are equal.
 * 	   The index is p.
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
const Real pi = acos(-1.0);

int A1, A2, A3, A4, B1, B2, C, x1, x2, p, q;

void input() {
	scanf("%d %d %d %d %d %d %d", &A1, &A2, &A3, &A4, &B1, &B2, &C);
	scanf("%d %d", &x1, &x2);
}

int f(int x, int y) {
	int h = A1 * x * y + A2 * x + A3 * y + A4;
	if (h > B1) {
		h = (h - B2) % C + B2;
		while (h > B2)
			h -= C;
	}
	return h;
}

void advance(int &i, int &a1, int &a2) {
	int t = f(a1, a2);
	a1 = a2;
	a2 = t;
	i++;
}

void solve() {
	int i, j, a1, a2, b1, b2;
	a1 = b1 = x1; a2 = b2 = x2; i = j = 1;
	do {
		advance(i, a1, a2);
		advance(j, b1, b2); advance(j, b1, b2);
	} while (a1 != b1 || a2 != b2);
	q = j - i; p = i;

	a1 = b1 = x1; a2 = b2 = x2; i = j = 1;
	for (int k = 0; k < p; k++) {
		advance(i, a1, a2);
		advance(j, b1, b2);
	}
	do {
		advance(j, b1, b2);
	} while (a1 != b1 || a2 != b2);
	q = j - i;

	a1 = b1 = x1; a2 = b2 = x2; i = j = 1;
	for (int k = 0; k < q; k++)
		advance(j, b1, b2);
	while (a1 != b1 || a2 != b2) {
		advance(i, a1, a2);
		advance(j, b1, b2);
	}
	p = i;
}

void output() {
	printf("%d %d\n", p, q);
}

int main() {
	input();
	solve();
	output();
	return 0;
}


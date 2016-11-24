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

long long p, q;
long long ans;

bool input() {
	long double rp, rq;
	if (scanf("%Lf %Lf", &rp, &rq) == EOF)
		return false;
	p = (int)(rp * 100 + 0.5);
	q = (int)(rq * 100 + 0.5);
	return true;
}

long long upper(long long a, long long b) {
	return a / b + 1;
}

long long lower(long long a, long long b) {
	if (a % b == 0)
		return a / b - 1;
	else
		return a / b;
}

void solve() {
	for (long long n = 1; ; n++) {
		if (upper(p * n, 10000) <= lower(q * n, 10000)) {
			ans = n;
			break;
		}
	}
}

void output() {
	printf("%lld\n", ans);
}

int main() {
	while (input()) {
		solve();
		output();
	}
	return 0;
}


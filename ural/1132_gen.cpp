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

const int T = 100000;

bool is_prime(int a) {
	for (int c = 2; c <= min(a - 1, (int)(sqrt((double)a) + 0.5)); c++) {
		if (a % c == 0)
			return false;
	}
	return true;
}

int main() {
	vector<int> prime;
	prime.clear();
	for (int i = 2; i <= 32767; i++) {
		if (is_prime(i))
			prime.push_back(i);
	}
	FILE *fout = fopen("1132_0.in", "w");
	fprintf(fout, "%d\n", T);
	for (int I = 0; I < T; I++) {
		int n = prime[rand() % prime.size()];
		int a = rand() % (n - 1) + 1;
		fprintf(fout, "%d %d\n", a, n);
	}
	fclose(fout);
	return 0;
}


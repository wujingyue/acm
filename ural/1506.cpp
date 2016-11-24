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

int a[max_n];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int len = (n + k - 1) / k;
	for (int i = 0; i < len; i++) {
		for (int j = i; j < n; j += len)
			printf("%4d", a[j]);
		printf("\n");
	}
	return 0;
}


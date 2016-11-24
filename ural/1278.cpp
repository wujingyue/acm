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

vector<int> a;

int main() {
	int m;
	scanf("%d", &m);
	a.clear(); a.push_back(-1);
	int p = 0;
	for (int k = 1; k * 2 <= m; k *= 2) {
		a.push_back(p);
		p++;
	}
	// cerr << p << endl;
	for (int i = p - 1; i >= 0; i--) {
		if ((m & (1 << i)) > 0)
			a.push_back(i);
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] == -1)
			printf("BELL&RET\n");
		else
			printf("CALL %d\n", a.size() - 1 - a[i]);
	}
	return 0;
}


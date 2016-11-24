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

const int n = 10000;

int main() {
	FILE *fout = fopen("1505_0.in", "w");
	fprintf(fout, "%d\n", n);
	for (int i = 1; i < n; i++) {
		fprintf(fout, "%d %d %d %d.\n", i + 1, 1, 1, 1000000);
	}
	fprintf(fout, ".\n");
	fclose(fout);
	return 0;
}


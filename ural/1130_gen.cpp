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
	FILE *fout = fopen("1130_0.in", "w");
	fprintf(fout, "%d\n", n);
	fprintf(fout, "1000\n");
	for (int i = 0; i < n; i++) {
		int x = rand() % 200 - 100, y = rand() % 200 - 100;
		fprintf(fout, "%d %d\n", x, y);
	}
	fclose(fout);
	return 0;
}


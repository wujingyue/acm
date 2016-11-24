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

const int n = 50000;

int main() {
	FILE *fout = fopen("1587_0.in", "w");
	fprintf(fout, "%d\n", n);
	for (int i = 0; i < n; i++)
		fprintf(fout, "%d ", rand() % 3 + 1);
	fprintf(fout, "\n");
	fclose(fout);
	return 0;
}


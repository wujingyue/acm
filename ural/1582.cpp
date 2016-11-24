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

int main() {
	long double k1, k2, k3;
	scanf("%Lf %Lf %Lf", &k1, &k2, &k3);
	k1 = 1 / k1; k2 = 1 / k2; k3 = 1 / k3;
	printf("%.0Lf\n", 1000 / (k1 + k2 + k3));
	return 0;
}


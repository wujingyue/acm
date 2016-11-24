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

const int max_n = 1024;

struct Record {
	int x, y, diff, father;
};

int n;
int a[max_n], b[max_n];
Record q[max_n * max_n * 3];
bool visit[max_n][max_n][3];

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		char ch;
		cin >> ch;
		a[i] = (ch == '0' ? 0 : 1);
	}
	for (int i = 0; i < n; i++) {
		char ch;
		cin >> ch;
		b[i] = (ch == '0' ? 0 : 1);
	}
}

void print_sol(int i) {
	if (q[i].father == -1)
		return;
	int j = q[i].father;
	print_sol(j);
	if (q[j].x < q[i].x)
		printf("1");
	else
		printf("2");
}

void solve() {
	int head, tail;
	memset(visit, 0, sizeof visit);
	head = 0; tail = 1; q[0].x = 0; q[0].y = 0; q[0].diff = 1; q[0].father = -1;
	visit[0][0][1] = true;
	while (head < tail) {
		int x = q[head].x, y = q[head].y, diff = q[head].diff;
		if (x == n && y == n) {
			assert(diff == 1);
			print_sol(head);
			printf("\n");
			return;
		}
		if (x < n) {
			int x1 = x + 1, y1 = y, diff1 = diff + a[x] * 2 - 1;
			if (diff1 >= 0 && diff1 <= 2 && !visit[x1][y1][diff1]) {
				q[tail].x = x1; q[tail].y = y1; q[tail].diff = diff1; q[tail].father = head;
				tail++;
				visit[x1][y1][diff1] = true;
			}
		}
		if (y < n) {
			int x1 = x, y1 = y + 1, diff1 = diff + b[y] * 2 - 1;
			if (diff1 >= 0 && diff1 <= 2 && !visit[x1][y1][diff1]) {
				q[tail].x = x1; q[tail].y = y1; q[tail].diff = diff1; q[tail].father = head;
				tail++;
				visit[x1][y1][diff1] = true;
			}
		}
		head++;
	}
	printf("Impossible\n");
}

void output() {}

int main() {
	input();
	solve();
	output();
	return 0;
}


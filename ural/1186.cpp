/**
 * handle formula separately
 * ...2 (... should be separated by + rather than *
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

struct Result {
	int num;
	map<string, int> res;
};

vector<string> ir_a, ir_b;
map<string, int> res_a, res_b;
string a, b;
int n;

vector<string> convert(const string &a) {
	vector<string> tokens;
	for (size_t i = 0; i < a.length();) {
		// cerr << "ch = " << a[i] << endl;
		if (a[i] == '+' || a[i] == '(' || a[i] == ')') {
			tokens.push_back(string(1, a[i]));
			i++;
		} else if (isdigit(a[i])) {
			size_t j = i + 1;
			while (j < a.length() && isdigit(a[j]))
				j++;
			tokens.push_back(a.substr(i, j - i));
			i = j;
		} else {
			assert(isupper(a[i]));
			size_t j = i + 1;
			while (j < a.length() && islower(a[j]))
				j++;
			tokens.push_back(a.substr(i, j - i));
			i = j;
		}
	}
#if 0
	for (size_t i = 0; i < tokens.size(); i++)
		cerr << ' ' << tokens[i];
	cerr << endl;
#endif
	// 2 ( )
	size_t i = 0;
	while (i < tokens.size()) {
		size_t j = i + 1;
		while (j < tokens.size() && tokens[j] != "+")
			j++;
		if (isdigit(tokens[i][0])) {
			tokens.insert(tokens.begin() + j, ")");
			j++;
			assert(j >= tokens.size() || tokens[j] == "+");
			tokens.insert(tokens.begin() + (i + 1), "(");
			tokens.insert(tokens.begin() + (i + 1), "*");
			j += 2;
			assert(j >= tokens.size() || tokens[j] == "+");
		}
		i = j + 1;
	}
	vector<string> ir;
	for (size_t i = 0; i < tokens.size(); ++i) {
		ir.push_back(tokens[i]);
		if (i + 1 < tokens.size()) {
			// add operator between tokens[i] and tokens[i + 1]
			if (isupper(tokens[i][0]) && isupper(tokens[i + 1][0]))
				ir.push_back("+");
			else if (isupper(tokens[i][0]) && isdigit(tokens[i + 1][0]))
				ir.push_back("*");
			else if (isdigit(tokens[i][0]) && isupper(tokens[i + 1][0]))
				ir.push_back("+");
			else if (isupper(tokens[i][0]) && tokens[i + 1] == "(")
				ir.push_back("+");
			else if (tokens[i] == ")" && isupper(tokens[i + 1][0]))
				ir.push_back("+");
			else if (isdigit(tokens[i][0]) && tokens[i + 1] == "(")
				ir.push_back("+");
			else if (tokens[i] == ")" && isdigit(tokens[i + 1][0]))
				ir.push_back("*");
			else if (tokens[i] == ")" && tokens[i + 1] == "(")
				ir.push_back("+");
		}
	}
#if 0
	for (size_t i = 0; i < ir.size(); ++i)
		cerr << ' ' << ir[i];
	cerr << endl;
#endif
	return ir;
}

void calc(vector<Result> &opr, vector<string> &opt) {
	assert(!opt.empty() && opr.size() >= 2);
	if (opt.back() == "+") {
		int m = opr.size();
		assert(opr[m - 1].num == 0 && opr[m - 2].num == 0);
		for (map<string, int>::iterator it = opr[m - 1].res.begin(); it != opr[m - 1].res.end(); ++it)
			opr[m - 2].res[it->first] += it->second;
		opr.pop_back();
		opt.pop_back();
	} else if (opt.back() == "*") {
		int m = opr.size();
		assert(opr[m - 2].num == 0 || opr[m - 1].num == 0);
		if (opr[m - 2].num > 0 && opr[m - 1].num > 0)
			opr[m - 2].num *= opr[m - 1].num;
		else {
			if (opr[m - 2].num > 0)
				swap(opr[m - 2], opr[m - 1]);
			for (map<string, int>::iterator it = opr[m - 2].res.begin(); it != opr[m - 2].res.end(); ++it)
				it->second *= opr[m - 1].num;
		}
		opr.pop_back();
		opt.pop_back();
	} else
		assert(false);
}

map<string, int> eval(const vector<string> &ir) {
	vector<string> opt;
	vector<Result> opr;
	for (size_t i = 0; i < ir.size(); ++i) {
		if (isupper(ir[i][0])) {
			Result tmp;
			tmp.num = 0;
			tmp.res[ir[i]] = 1;
			opr.push_back(tmp);
		} else if (isdigit(ir[i][0])) {
			Result tmp;
			tmp.num = atoi(ir[i].c_str());
			opr.push_back(tmp);
		} else if (ir[i] == "*" || ir[i] == "(")
			opt.push_back(ir[i]);
		else if (ir[i] == ")") {
			while (opt.back() != "(")
				calc(opr, opt);
			opt.pop_back();
		} else {
			assert(ir[i] == "+");
			while (!opt.empty() && (opt.back() == "*" || opt.back() == "+"))
				calc(opr, opt);
			opt.push_back(ir[i]);
		}
	}
	while (!opt.empty())
		calc(opr, opt);
	assert(opr.size() == 1);
#if 0
	for (map<string, int>::iterator it = opr.back().res.begin(); it != opr.back().res.end(); ++it) {
		cerr << it->first << " * " << it->second << endl;
	}
#endif
	return opr.back().res;
}

void input() {
	cin >> a;
	ir_a = convert(a);
	res_a = eval(ir_a);
}

bool compare(const map<string, int> &a, const map<string, int> &b) {
	if (a.size() != b.size())
		return false;
	map<string, int>::const_iterator i = a.begin(), j = b.begin();
	while (i != a.end()) {
		assert(j != b.end());
		if (*i != *j)
			return false;
		++i; ++j;
	}
	return true;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> b;
		ir_b = convert(b);
		res_b = eval(ir_b);
		if (compare(res_a, res_b))
			cout << a << "==" << b << endl;
		else
			cout << a << "!=" << b << endl;
	}
}

void output() {}

int main() {
	input();
	solve();
	output();
	return 0;
}


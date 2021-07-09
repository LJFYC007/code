#include "testlib.h"
#include <bits/stdc++.h>

typedef std::map<int, bool> map;
typedef map::iterator it;
typedef map::value_type value;

map number;

it split(int x) {
	it p = number.lower_bound(x); if (p->first == x) return p;
	return number.emplace(x, (--p)->second).first;
}

void add(int x) {
	it l = split(x), r = l;
	while (r->second) ++r; int y = r->first;
	number.erase(l, r), number.emplace(x, 0);
	number.emplace(y + 1, 0), number[y] = 1;
}
void del(int x) {
	it l = split(x), r = l;
	while (r != number.end() && !r->second) ++r;

	ensuref(r != number.end(), "n must > 0 qaq");

	int y = r->first;
	number.erase(l, r), number.emplace(x, 1);
	number.emplace(y + 1, 1), number[y] = 0;
}

int ctz() {
	it i = number.begin();
	while (i != number.end() && !(i->second)) if (i->first) number.erase(i++); else ++i;
	
	ensuref(i != number.end(), "n must > 0 qwq");
	
	return i->first;
}

int main(int argc, char *argv[]) {
	registerValidation(argc, argv);
	int n = inf.readInt(1, 150000); inf.readSpace();
	int m = inf.readInt(0, 150000); inf.readEoln();
	int lst = -1;
	for (int i = 0, l, r; i < n; ++i) {
		l = inf.readInt(lst + 1, 1000000000, "l");
		inf.readSpace();
		r = inf.readInt(l, 1000000000, "r");
		inf.readEoln();
		++r;
		number.emplace(l, 1), number.emplace(r, 0);
	}
	number.emplace(1 << 30, 0);
	if (number.begin()->first != 0) number.emplace(0, 0);
	while (m--) {
		int opt = inf.readInt(0, 1, "opt"); inf.readSpace();
		int b = inf.readInt(0, 1000000000, "b"); inf.readEoln();
		opt ? del(b) : add(b);
	}
	inf.readEof();
	return 0;
}

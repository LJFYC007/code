#include <bits/stdc++.h>

typedef long long LL;
typedef std::map<int, bool> map;
typedef map::iterator it;
typedef map::value_type value;

const int B = 15, M = 1 << B, mod = 998244353;
void reduce(int &x) { x += x >> 31 & mod; }
int _reduce(int x) { return x + (x >> 31 & mod); }

int pa[M + 1], pb[M];
void init() {
	pa[0] = pb[0] = 1;
	for (int i = 1; i <= M; ++i)
		reduce(pa[i] = (pa[i - 1] << 1) - mod);
	pb[1] = pa[M];
	for (int i = 2; i < M; ++i)
		pb[i] = (LL) pb[i - 1] * pb[1] % mod;
}
int pow(int x) { return (LL) pa[x & M - 1] * pb[x >> B] % mod; }

map number;

int prefix(int x) { return x < 0 ? 1 : (4 + x * (x + 3LL) % mod) % mod * pow(x) % mod; }
int qaq(int x) { return (x + 1LL) * pow(x + 1) % mod; }
int interval(int l, int r) { return _reduce(prefix(r - 1) - prefix(l - 1)); }
int ans = 0;
void add(int l, int r) { reduce(ans += interval(l, r) - mod); }
void del(int l, int r) { reduce(ans -= interval(l, r)); }

it split(int x) {
	it p = number.lower_bound(x);
	if (p->first == x) return p;
	return number.emplace(x, (--p)->second).first;
}

void add(int x) {
	it l = split(x), r = l;
	while (r->second) ++r; int y = r->first;
	del(x, y), add(y, y + 1), number.erase(l, r);
	number.emplace(x, 0), number.emplace(y + 1, 0), number[y] = 1;
}
void del(int x) {
	it l = split(x), r = l;
	while (r != number.end() && !r->second) ++r;
	int y = r->first;
	add(x, y), del(y, y + 1), number.erase(l, r);
	number.emplace(x, 1), number.emplace(y + 1, 1), number[y] = 0;
}

int ctz() {
	it i = number.begin();
	while (i != number.end() && !(i->second)) if (i->first) number.erase(i++); else ++i;
	return i->first;
}

int main() {
	std::ios::sync_with_stdio(0), std::cin.tie(0);
	int n, m; std::cin >> n >> m, init();
	for (int i = 0, l, r; i < n; ++i)
		std::cin >> l >> r, ++r, number.emplace(l, 1), number.emplace(r, 0), add(l, r);
	number.emplace(1 << 30, 0);
	if (number.begin()->first != 0) number.emplace(0, 0);
	while (m--) {
		int opt, b; std::cin >> opt >> b;
		opt ? del(b) : add(b), std::cout << _reduce(ans - qaq(ctz())) << '\n';
	}
	return 0;
}

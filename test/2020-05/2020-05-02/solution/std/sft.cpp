#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int N = 1e5;
const int INF = 1e9;

int n, m, a[N + 9];

struct info {
	int min, minc, se, addm, adds, sz;
	ll sum;
	void cleartag() {
		addm = adds = 0;
	}
	void clear() {
		min = INF, minc = 0, se = INF + 1, sz = 0, sum = 0;
	}
	void init(int v) {
		addm = adds = 0;
		if(v == INF) clear();
		else min = v, minc = 1, se = INF, sz = 1, sum = v;
	}
	void update(int addm1, int adds1) {
		min += addm1, addm += addm1;
		if(se < INF) se += adds1, adds += adds1;
		sum += (ll)minc * addm1 + (ll)(sz - minc) * adds1;
	}
	void pushup(const info &p) {
		if(p.min == min) minc += p.minc, chkmin(se, p.se);
		else if(p.min < min) se = std::min(min, p.se), min = p.min, minc = p.minc;
		else chkmin(se, p.min);
		sz += p.sz, sum += p.sum;
	}
	void pushdown(info &p) {
		if(p.min + addm == min) p.update(addm, adds);
		else p.update(adds, adds);
	}
};

struct node {
	info o, m, s;
}p[N * 4 + 9];

void pushdown(int x) {
	node &X = p[x], &L = p[x << 1], &R = p[x << 1 | 1];
	X.o.pushdown(L.o), X.o.pushdown(R.o);
	if(L.o.min == X.o.min) X.m.pushdown(L.m);
	else X.s.pushdown(L.m);
	if(R.o.min == X.o.min) X.m.pushdown(R.m);
	else X.s.pushdown(R.m);
	X.s.pushdown(L.s), X.s.pushdown(R.s);
	X.o.cleartag(), X.m.cleartag(), X.s.cleartag();
}

void pushup(int x) {
	node &X = p[x], &L = p[x << 1], &R = p[x << 1 | 1];
	X.o.clear(), X.m.clear(), X.s.clear();
	X.o.pushup(L.o), X.o.pushup(R.o);
	if(X.o.min == L.o.min) X.m.pushup(L.m);
	else X.s.pushup(L.m);
	if(X.o.min == R.o.min) X.m.pushup(R.m);
	else X.s.pushup(R.m);
	X.s.pushup(L.s), X.s.pushup(R.s);
}

void build(int x, int l, int r) {
	if(l == r) {
		node &X = p[x];
		X.o.init(a[l]);
		X.m.init(0);
		X.s.init(INF);
		return ;
	}
	int mid = (l + r) >> 1;
	build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	pushup(x); 
}

void dfsm(int x, int l, int r, int qx, int qy) {
	node &X = p[x];
	if(X.o.min == qy) {
		if(X.m.min + qx >= 0) X.m.update(qx, qx);
		else if(X.m.se + qx >= 0) X.m.update(-X.m.min, qx);
		else {
			pushdown(x);
			int mid = (l + r) >> 1;
			dfsm(x << 1, l, mid, qx, qy);
			dfsm(x << 1 | 1, mid + 1, r, qx, qy);
			pushup(x);
		}
	}
	else return ;
}

void dfso(int x, int l, int r, int qx) {	
	node &X = p[x];
	if(X.o.min >= qx) return ;
	else if(X.o.se > qx) {
		int add = qx - X.o.min;
		X.o.update(add, 0);
		dfsm(x, l, r, add, X.o.min);
		return ;
	}
	else {
		pushdown(x);
		int mid = (l + r) >> 1;
		dfso(x << 1, l, mid, qx);
		dfso(x << 1 | 1, mid + 1, r, qx);
		pushup(x);
	}
}

void max(int x, int l, int r, int ql, int qr, int qx) {
	if(ql <= l && r <= qr)
		dfso(x, l, r, qx);
	else {
		pushdown(x);
		int mid = (l + r) >> 1;
		if(ql <= mid) max(x << 1, l, mid, ql, qr, qx);
		if(qr > mid) max(x << 1 | 1, mid + 1, r, ql, qr, qx);
		pushup(x);
	}
}

void dfs(int x, int l, int r, int qx, bool f1, bool f2) {
	node &X = p[x];
	if(f1) {
		if(X.m.min + qx >= 0) X.m.update(qx, qx), f1 = false;
		else if(X.m.se + qx >= 0) X.m.update(-X.m.min, qx), f1 = false;
	}
	if(f2) {
		if(X.s.min + qx >= 0) X.s.update(qx, qx), f2 = false;
		else if(X.s.se + qx >= 0) X.s.update(-X.s.min, qx), f2 = false;
	}
	if(f1 || f2) {
		pushdown(x);
		int mid = (l + r) >> 1;
		dfs(x << 1, l, mid, qx, p[x << 1].o.min == X.o.min ? f1 : f2, f2);
		dfs(x << 1 | 1, mid + 1, r, qx, p[x << 1 | 1].o.min == X.o.min ? f1 : f2, f2);
		pushup(x);
	}
}

void add(int x, int l, int r, int ql, int qr, int qx) {
	if(ql <= l && r <= qr) {
		p[x].o.update(qx, qx);
		dfs(x, l, r, qx, true, true);
	}
	else {
		pushdown(x);
		int mid = (l + r) >> 1;
		if(ql <= mid) add(x << 1, l, mid, ql, qr, qx);
		if(qr > mid) add(x << 1 | 1, mid + 1, r, ql, qr, qx);
		pushup(x);
	}
}

ll qsum1(int x, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return p[x].o.sum;
	pushdown(x);
	int mid = (l + r) >> 1;ll ret = 0;
	if(ql <= mid) ret += qsum1(x << 1, l, mid, ql, qr);
	if(qr > mid) ret += qsum1(x << 1 | 1, mid + 1, r, ql, qr);
	return ret;
}

ll qsum2(int x, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return p[x].o.sum - p[x].m.sum - p[x].s.sum;
	pushdown(x);
	int mid = (l + r) >> 1;ll ret = 0;
	if(ql <= mid) ret += qsum2(x << 1, l, mid, ql, qr);
	if(qr > mid) ret += qsum2(x << 1 | 1, mid + 1, r, ql, qr);
	return ret;
}

int main() {
	freopen("sft.in", "r", stdin);
	freopen("sft.out", "w", stdout);

	read(n), read(m);
	for(int i = 1; i <= n; ++i) read(a[i]);
	build(1, 1, n);
	while(m--) {
		int tp, l, r, x;
		read(tp), read(l), read(r);
		if(tp <= 2) {
			read(x);
			if(tp == 1) max(1, 1, n, l, r, x);
			else add(1, 1, n, l, r, x);
		}
		else {
			ll ans;
			if(tp == 3) ans = qsum1(1, 1, n, l, r);
			else ans = qsum2(1, 1, n, l, r);
			printf("%lld\n", ans);
		}
	}
	
	fclose(stdin);fclose(stdout);
	return 0;
}

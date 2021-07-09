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
const int MOD = 998244353, INV2 = (MOD + 1) / 2;

int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

struct num {
	int a, b;// a + b * sqrt(5)
	num() {a = b = 0;}
	num(int _a, int _b):a(_a), b(_b) {}
	friend num operator + (const num &p, const num &q) {
		return num((p.a + q.a) % MOD, (p.b + q.b) % MOD);
	}
	friend num operator - (const num &p, const num &q) {
		return num((p.a - q.a + MOD) % MOD, (p.b - q.b + MOD) % MOD);
	}
	friend num operator * (const num &p, const num &q) {
		return num(((ll)p.a * q.a + 5ll * p.b * q.b) % MOD, ((ll)p.a * q.b + (ll)p.b * q.a) % MOD);
	}
	friend num operator * (const num &p, const int &q) {
		return num((ll)p.a * q % MOD, (ll)p.b * q % MOD);
	}
	num inv() {
		int dn = fpm(((ll)a * a % MOD - 5ll * b * b % MOD + MOD) % MOD, MOD - 2);
		return num((ll)a * dn % MOD, (ll)(MOD - b) * dn % MOD);
	}
}U = num(INV2, INV2), V = num(INV2, MOD - INV2);

num fpm(num a, int b) {
	num ret = num(1, 0);
	while(b) {
		if(b & 1) ret = ret * a;
		a = a * a, b >>= 1;
	}
	return ret;
}

struct info {
	num prd, pre, suf, ans;
	int sz;
	void init(num v) {
		prd = pre = suf = ans = v, sz = 1;
	}
	friend info operator + (const info &p, const info &q) {
		info ret;
		ret.prd = p.prd * q.prd;
		ret.pre = p.pre + q.pre * p.prd;
		ret.suf = q.suf + p.suf * q.prd;
		ret.ans = p.ans + q.ans + p.suf * q.pre;
		ret.sz = p.sz + q.sz;
		return ret;
	}
	void updrev() {
		std::swap(pre, suf);
	}
	void updagn(const num &t) {
		prd = fpm(t, sz);
		if(t.a == 1 && t.b == 0) {
			pre = suf = num(sz, 0);
			ans = num((ll)(sz + 1) * sz / 2 % MOD, 0);
		}
		else {
			num inv = (t - num(1, 0)).inv();
			num tmp = fpm(t, sz + 1);
			num prod = (tmp - t) * inv;
			pre = suf = prod;
			ans = prod * (sz + 1) - (tmp * sz - prod) * inv;
		}
	}
};

struct node {
	node *fa, *c[2];

	bool rev;
	num ta, tb;
	
	num a, b;
	info u, v;

	void init(int x) {
		ta = tb = num(-1, -1), rev = false, fa = c[0] = c[1] = 0;
		a = fpm(U, x), u.init(a), b = fpm(V, x), v.init(b);
	}
	
	void setc(node *x, int d) {
		c[d] = x;
		if(x) x->fa = this;
	}
	bool isroot() {
		return !fa || (fa->c[0] != this && fa->c[1] != this);
	}
	bool dir() {
		return fa->c[1] == this;
	}
	void updrev() {
		rev ^= true;
		u.updrev(), v.updrev();
	}
	void upda(const num &t) {
		ta = a = t, u.updagn(t);
	}
	void updb(const num &t) {
		tb = b = t, v.updagn(t);
	}
	void pushdown() {
		if(rev) {
			rev = false;
			std::swap(c[0], c[1]);
			for(int i = 0; i < 2; ++i)
				if(c[i]) c[i]->updrev();
		}
		if(ta.a != -1) {
			for(int i = 0; i < 2; ++i)
				if(c[i]) c[i]->upda(ta);
			ta = num(-1, -1);
		}
		if(tb.a != -1) {
			for(int i = 0; i < 2; ++i)
				if(c[i]) c[i]->updb(tb);
			tb = num(-1, -1);
		}
	}
	void pushup() {
		u.init(a), v.init(b);
		if(c[0]) u = c[0]->u + u, v = c[0]->v + v;
		if(c[1]) u = u + c[1]->u, v = v + c[1]->v;
	}
	void rot() {
		node *f = fa;
		int d = dir();
		if(f->isroot()) fa = f->fa;
		else f->fa->setc(this, f->dir());
		f->setc(c[d ^ 1], d), setc(f, d ^ 1);
		f->pushup();
	}
	void splay() {
		static node *anc[N + 9];
		int ancn = 0;
		anc[++ancn] = this;
		for(node *p = this; !p->isroot(); p = p->fa)
			anc[++ancn] = p->fa;
		while(ancn) anc[ancn--]->pushdown();
		while(!isroot()) {
			if(!fa->isroot()) {
				if(fa->dir() == dir()) fa->rot();
				else rot();
			}
			rot();
		}
		pushup();
	}
	void access() {
		for(node *p = this, *q = 0; p; q = p, p = p->fa)
			p->splay(), p->setc(q, 1), p->pushup();
	}
	void beroot() {
		access(), splay(), updrev();
	}
}p[N + 9];

int n, m, fa[N + 9];

void link(node *p, node *q) {
	p->beroot(), p->fa = q;
}

void cut(node *p, node *q) {
	p->beroot(), q->access(), q->splay();
	p->fa = q->c[0] = 0;
	q->pushup();
}

void agn(node *p, node *q, const num &ta, const num &tb) {
	p->beroot(), q->access(), q->splay();
	q->upda(ta), q->updb(tb);
}

int get(const num &p, const num &q) {
	return (p - q).b;
}

int qry(node *p) {
	p->splay();
	return get(p->a, p->b);
}

int qry(node *p, node *q) {
	p->beroot(), q->access();
	q->splay();
	return get(q->u.ans, q->v.ans);
}

int main() {
	freopen("st.in", "r", stdin);
	freopen("st.out", "w", stdout);

	read(n), read(m);
	for(int i = 1, x; i <= n; ++i) read(x), p[i].init(x);
	for(int i = 2, x; i <= n; ++i) read(x), link(p + x, p + i), fa[i] = x;
	while(m--) {
		int tp, u, v, x;
		read(tp), read(u);
		if(tp == 1) {
			read(v);
			cut(p + u, p + fa[u]);
			fa[u] = v;
			link(p + u, p + fa[u]);
		}
		else if(tp == 2) {
			read(v), read(x);
			num ta = fpm(U, x), tb = fpm(V, x);
			agn(p + u, p + v, ta, tb);
		}
		else if(tp == 3) printf("%d\n", qry(p + u));
		else read(v), printf("%d\n", qry(p + u, p + v));
	}
	
	fclose(stdin);fclose(stdout);
	return 0;
}

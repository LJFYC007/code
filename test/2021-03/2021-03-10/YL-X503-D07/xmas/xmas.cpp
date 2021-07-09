#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>

const int maxn = 20010;
const int maxm = 2e6 + 10;

int T, K, P, n, q, datatype, Begin[maxn], Next[maxn], To[maxn], e, G, omega, t[maxn];
int anc[maxn], id[maxn], tot, size[maxn], deg[maxn], ll[maxn], rr[maxn], pre[maxm], suf[maxm];
vector<int> p, ccc[210], III;
struct node { vector<int> val, lazy; int len; bool tag; } Tree[maxn << 2];

vector<int> operator *(vector<int> a, vector<int> b) { vector<int> c(K); REP(i, 0, K - 1) c[i] = 1ll * a[i] * b[i] % P; return c; }
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % P; a = 1ll * a * a % P; b >>= 1; } return r; } 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 
inline void INIT(vector<int> &f) { f.resize(K); REP(i, 0, K - 1) f[i] = 1; } 
inline void Print(vector<int> f, int x) { int ret = 0; REP(i, 0, K - 1) ret = (ret + 1ll * ccc[i][x] * f[i]) % P; printf("%d", (ret + P) % P); }
inline vector<int> power(vector<int> a, int b) 
{ 
	vector<int> c(K); 
	REP(i, 0, K - 1) c[i] = !a[i] ? !b : suf[1ll * pre[a[i]] * b % (P - 1)]; 
	return c; 
} 

vector<int> Mul(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(); vector<long long> c(K);
	REP(i, 0, n - 1) REP(j, 0, m - 1) c[(i + j) % K] += 1ll * a[i] * b[j];
	vector<int> d(K); REP(i, 0, K - 1) d[i] = c[i] % P; return d;
}

inline void PushTag(int root, vector<int> a) 
{ 
	Tree[root].val = Tree[root].val * power(a, Tree[root].len); 
	Tree[root].lazy = Tree[root].lazy * a; Tree[root].tag = true; 
} 
inline void PushUp(int root) { Tree[root].val = Tree[lson].val * Tree[rson].val; } 
inline void PushDown(int root)
{
	if ( !Tree[root].tag ) return ; 
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].tag = false; INIT(Tree[root].lazy);
}

inline void Modify(int root, int l, int r, int L, int R)
{
	if ( L > R ) return ;
	if ( L <= l && r <= R ) { PushTag(root, p); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R);
	PushUp(root);
}

inline vector<int> Query(int root, int l, int r, int L, int R)
{
	if ( L > R ) return III;
	if ( L <= l && r <= R ) return Tree[root].val;
	int Mid = l + r >> 1; vector<int> ret = III; PushDown(root);
	if ( L <= Mid ) ret = ret * Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret = ret * Query(rson, Mid + 1, r, L, R);
	return ret;
}
inline void Build(int root, int l, int r)
{
	INIT(Tree[root].val); INIT(Tree[root].lazy); Tree[root].tag = false; Tree[root].len = r - l + 1;
	if ( l == r ) return ; int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Insert1(int v, int a) { REP(i, 0, K - 1) p[i] = (1 + power(t[i], a)) % P; Modify(1, 1, n, id[v], id[v]); }
inline void Insert2(int v, int a, int b) { REP(i, 0, K - 1) p[i] = (1 + power(t[i], a) + power(t[i], b)) % P; Modify(1, 1, n, id[v], id[v]); }

inline bool Check()
{
	int x = P - 1;
	for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
	{
		if ( power(G, (P - 1) / i) == 1 ) return false;
		while ( x % i == 0 ) x /= i;
	}
	if ( x > 1 && power(G, (P - 1) / x) == 1 ) return false;
	return true;
} 

inline void DFS(int u, int fa)
{
	size[u] = 1; ll[u] = tot + 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		id[v] = ++ tot; anc[v] = u;
	}
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) { DFS(To[i], u); size[u] += size[To[i]]; } 
	rr[u] = tot;
}
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("xmas.in", "r", stdin);
	freopen("xmas.out", "w", stdout);
#endif
	scanf("%d%d%d", &T, &K, &P); p.resize(K); INIT(III);
	G = 2; while ( !Check() ) ++ G; omega = power(G, (P - 1) / K);
	t[0] = 1; REP(i, 1, K - 1) t[i] = 1ll * t[i - 1] * omega % P;
	REP(i, 0, K - 1) 
	{
		ccc[i].resize(1, 1);
		REP(j, 0, K - 1) if ( i != j ) 
		{
			int val = power(t[i] - t[j], P - 2);
			vector<int> a(2); a[1] = val; a[0] = 1ll * -t[j] * val % P;
			ccc[i] = Mul(ccc[i], a);
		}
	}
	int x = 1; pre[x] = 0; suf[0] = x; REP(i, 1, P - 2) { x = x * G % P; pre[x] = i; suf[i] = x; } 
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &q, &datatype); e = tot = 0; REP(i, 1, n) Begin[i] = deg[i] = 0; 
		REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); ++ deg[u]; ++ deg[v]; } 
		id[1] = ++ tot; DFS(1, 0); 

		Build(1, 1, n);
		while ( q -- ) 
		{
			char c = getchar(); c = getchar();			
			if ( c == 'L' ) { int v, a; scanf("%d%d", &v, &a); Insert1(v, a); }
			if ( c == 'C' ) { int v, a, b; scanf("%d%d%d", &v, &a, &b); Insert2(v, a, b); }
			if ( c == 'F' ) 
			{
				int u; scanf("%d", &u); p = Query(1, 1, n, id[u], id[u]);
				if ( anc[u] ) 
				{
					Modify(1, 1, n, ll[u], ll[u] + deg[u] - 2);
					Modify(1, 1, n, id[anc[u]], id[anc[u]]);
				}
				else Modify(1, 1, n, ll[u], ll[u] + deg[u] - 1);
			}
			if ( c == 'S' ) 
			{ 
				int u, v; scanf("%d%d", &u, &v); p = Query(1, 1, n, id[u], id[u]);
				if ( anc[v] == u ) { Modify(1, 1, n, ll[v], rr[v]); Modify(1, 1, n, id[v], id[v]); }
				else { Modify(1, 1, n, 1, id[u] - 1); Modify(1, 1, n, id[u] + 1, ll[u] - 1); Modify(1, 1, n, rr[u] + 1, n); }
			}
			if ( c == 'Q' ) 
			{
				int u, v, x; scanf("%d%d%d", &u, &v, &x);
				if ( anc[u] == v ) 
				{ 
					Print(Query(1, 1, n, ll[u], rr[u]) * Query(1, 1, n, id[u], id[u]), x); putchar(' '); 
					Print(Query(1, 1, n, 1, id[u] - 1) * Query(1, 1, n, id[u] + 1, ll[u] - 1) * Query(1, 1, n, rr[u] + 1, n), x); 
				} 
				else 
				{
					Print(Query(1, 1, n, 1, id[v] - 1) * Query(1, 1, n, id[v] + 1, ll[v] - 1) * Query(1, 1, n, rr[v] + 1, n), x); 
					putchar(' '); Print(Query(1, 1, n, ll[v], rr[v]) * Query(1, 1, n, id[v], id[v]), x); 
				}
				puts("");
			}
		}
	}	
	return 0;
}

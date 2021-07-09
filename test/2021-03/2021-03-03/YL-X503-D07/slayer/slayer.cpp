#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, size[maxn], c[maxn];
int f[maxn], son[maxn], dis[maxn], id[maxn], p[maxn], tot, s[maxn], ret, top[maxn];

inline void Add(int &x, int y) { x = x + y >= Mod ? x + y - Mod : x + y; }

inline int lowbit(int x) { return x & -x; } 

inline void Modify(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) Add(c[i], val); }

inline int Query(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) Add(sum, c[i]); return sum; } 

inline int C(long long n) { return (n * (n - 1) / 2) % Mod; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u, int fa)
{
	size[u] = 1; 
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; f[v] = u;
		DFS1(v, u); size[u] += size[v]; Add(a[u], a[v]);
		if ( size[v] > size[son[u]] ) son[u] = v;
	}
}

inline void DFS2(int u, int t)
{
	id[u] = ++ tot; p[tot] = u; top[u] = t;
	if ( son[u] ) DFS2(son[u], t);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( son[u] == v || f[u] == v ) continue ; 
		Add(s[u], C(a[v])); DFS2(v, v);
	}
}

inline void Solve(int u, int w)
{
	while ( u ) 
	{
		Modify(id[top[u]], w); Modify(id[u] + 1, Mod - w);
		u = top[u]; int x = Query(id[u]);
		s[f[u]] = (s[f[u]] - C(x - w) + C(x)) % Mod;
		u = f[u];
	}
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

signed main()
{
	freopen("slayer.in", "r", stdin);
	freopen("slayer.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { read(a[i]); Add(ret, a[i]); } 
	REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); } 
	dis[1] = 1; DFS1(1, 0); DFS2(1, 1); 
	REP(i, 1, n) { Modify(id[i], a[i]); Modify(id[i] + 1, Mod - a[i]); }
	while ( m -- ) 
	{
		int op, x, y; read(op); read(x);
		if ( op == 1 ) { read(y); Add(ret, y); Solve(x, y); } 
		else 
		{
			int ans = (C(ret) - s[x]) % Mod;
			ans = (ans - C(ret - Query(id[x]))) % Mod;
			if ( son[x] ) ans = (ans - C(Query(id[son[x]]))) % Mod;
			printf("%d\n", (ans + Mod) % Mod);
		}
	}
	return 0;
}

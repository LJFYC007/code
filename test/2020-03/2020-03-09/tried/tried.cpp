#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int seed = 107;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], fac[maxn], dfn[maxn], low[maxn], tot;
int dis[maxn], anc[maxn][20], st[maxn][20], deg[maxn], p[maxn], N, f[maxn], h[maxn], g[2][maxn];
int id[maxn], Stack[maxn], top, cnt, size[maxn];
bool vis[maxn], use[maxn];
struct node{ int u, v, w; } a[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void toposort()
{
	queue<int> Q;
	REP(i, 1, n) if ( !deg[i] ) Q.push(i);
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop(); p[++ N] = u;
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i]; -- deg[v];
			if ( !deg[v] ) Q.push(v);
		}
	}
	if ( N != n ) { puts("inf\ninf\n"); exit(0); }
}

inline void PushUp(int u)
{
	REP(k, 1, 18)
	{
		anc[u][k] = anc[anc[u][k - 1]][k - 1];
		st[u][k] = (st[u][k - 1] + fac[k - 1] * st[anc[u][k - 1]][k - 1]) % Mod;
	}
}

inline int Check(int u, int v, int w)
{
	g[0][0] = v; g[1][0] = w;
	REP(j, 1, 18)
	{
		g[0][j] = anc[g[0][j - 1]][j - 1];
		g[1][j] = (g[1][j - 1] + fac[j - 1] * st[g[0][j - 1]][j - 1]) % Mod;
	}
	int x = u, y = u, len = 0;
	for ( int j = 18; j >= 0; -- j )
	{
		if ( anc[x][j] == 0 ) continue ;
		if ( st[x][j] != (y == u ? g[1][j] : st[y][j]) ) continue ;
		x = anc[x][j]; y = (y == u ? g[0][j] : anc[y][j]);
		len += 1 << j;
	}
	if ( anc[x][0] && st[x][0] < (y == u ? g[1][0] : st[y][0]) ) len = -1;
	return len;
}

inline int check(int u, int v)
{
	int len = 0;
	for ( int j = 18; j >= 0; -- j )
	{
		if ( !anc[u][j] || st[u][j] != st[v][j] ) continue ;
		u = anc[u][j]; v = anc[v][j]; len += 1 << j;
	}
	if ( anc[u][0] && st[u][0] < st[v][0] ) len = -1;
	return len;
}

inline int Solve()
{
	REP(i, 1, n) f[i] = 1; int ans = 0;
	for ( int i = n; i >= 1; -- i )
	{
		int u = p[i];
		for ( int j = Begin[u]; j; j = Next[j] ) f[u] = (f[u] + f[To[j]]) % Mod;
		ans = (ans + f[u]) % Mod;
	}
	return ans;
}

inline void read(int &x) { char c = getchar(); while ( c < '0' || c > '9' ) c = getchar(); x = 0; while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } }

inline void Tarjan(int u)
{
	low[u] = dfn[u] = ++ tot; Stack[++ top] = u;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
		else if ( !id[v] ) low[u] = min(low[u], dfn[v]);
	}
	if ( dfn[u] == low[u] )
	{
		++ cnt; ++ size[cnt];
		while ( Stack[top] != u ) { id[Stack[top --]] = cnt; ++ size[cnt]; }
		id[u] = cnt; -- top;
	}
}

signed main()
{
	freopen("tried.in", "r", stdin);
	freopen("tried.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) { read(a[i].v); read(a[i].u); read(a[i].w); if ( !a[i].w ) add(a[i].u, a[i].v, 0); }
	REP(i, 1, n) if ( !dfn[i] ) Tarjan(i);
	mem(Begin); e = 0;
	REP(i, 1, m)
	{
		if ( id[a[i].u] == id[a[i].v] ) continue ;
		add(id[a[i].u], id[a[i].v], a[i].w);
		++ deg[id[a[i].v]];
	}
	n = cnt;
	REP(i, 1, n)
	{
		if ( size[i] > 1 ) vis[i] = use[i] = true;
		if ( size[i] > 1 && deg[i] ) { puts("inf\ninf\n"); return 0; }
	}
	toposort();
	REP(i, 1, n) { f[i] = -1; if ( !Begin[i] ) { f[i] = 0; h[i] = 1; } }
	REP(i, 0, 18) fac[i] = power(seed, power(2, i)) % Mod;
	for ( int i = n; i >= 1; -- i )
	{
		int u = p[i];
		for ( int j = Begin[u]; j; j = Next[j] )
		{
			int v = To[j];
			if ( f[u] < f[v] + 1 )
			{
				f[u] = f[v] + 1; h[u] = h[v]; anc[u][0] = v; st[u][0] = W[j];
				use[u] = use[v] || vis[u];
				PushUp(u);
			}
			else if ( f[u] == f[v] + 1 )
			{
				int len = Check(u, v, W[j]);
				if ( len == f[u] ) { h[u] = (h[u] + h[v]) % Mod; use[u] = use[v] || vis[u]; }
				else if ( len == -1 )
				{
					h[u] = h[v]; anc[u][0] = v; st[u][0] = W[j];
					use[u] = use[v] || vis[u];
					PushUp(u);
				}
			}
		}
	}
	bool flag = use[1];
	int pos = 1, ans = h[1];
	REP(i, 2, n)
	{
		if ( f[i] > f[pos] ) { pos = i; ans = h[i]; flag = use[i]; continue ; }
		if ( f[i] < f[pos] ) continue ;
		int len = check(pos, i);
		if ( len == f[pos] ) { ans = (ans + h[i]) % Mod; flag = flag || use[i]; }
		else if ( len == -1 ) { pos = i; ans = h[i]; flag = use[i]; continue ; }
	}
	vector<int> t;
	while ( anc[pos][0] ) { t.push_back(st[pos][0]); pos = anc[pos][0]; }
	if ( !t.size() )
	{
		puts("0");
		if ( flag == true ) puts("inf");
		else printf("%lld\n", ans % Mod);
		return 0;
	}
	int x = 0; while ( x < t.size() - 1 && t[x] == 0 ) ++ x;
	REP(i, x, t.size() - 1) printf("%lld", t[i]); puts("");
	if ( x == t.size() - 1 && t[x] == 0 ) printf("%lld\n", Solve());
	else if ( flag == true ) puts("inf");
	else printf("%lld\n", ans % Mod);
	return 0;
}

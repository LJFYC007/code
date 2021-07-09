#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, dep[maxn], son[maxn], h1[maxn * 10];
int *f[maxn], *g[maxn], *h = h1, ans;

inline void add(int u, int v) {// printf("%lld %lld\n", u, v);
To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
	//printf("%lld %lld\n", u, fa);
	//printf("%lld\n", Begin[u]);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS1(v, u);
		dep[u] = max(dep[u], dep[v] + 1);
		if ( dep[v] > dep[son[u]] ) son[u] = v;
	}
}

inline void Solve(int u)
{
	f[u] = h; h += dep[u] + 1; g[u] = h + dep[u] + 1; h += (dep[u] + 1) * 2;
}

inline void DFS2(int u, int fa)
{
	if ( son[u] )
	{
		g[son[u]] = g[u] - 1; f[son[u]] = f[u] + 1;
		printf("%lld %lld\n", g[u][2], g[son[u]][1]);
		DFS2(son[u], u);
	}
	ans += g[u][0]; f[u][0] = 1;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || v == son[u] ) continue ;
		Solve(v); DFS2(v, u);
		for ( int j = dep[v]; j >= 0; -- j )
		{
			if ( j ) ans += f[u][j - 1] * g[v][j] + g[u][j + 1] * f[v][j];
			else ans += g[u][j + 1] * f[v][j];
			g[u][j + 1] += f[u][j + 1] * f[v][j];
		}
		REP(j, 0, dep[v])
		{
			if ( j ) g[u][j - 1] += g[v][j];
			f[u][j + 1] += f[v][j];
		}
	}
}

signed main()
{
    freopen("zh.in", "r", stdin);
	freopen("zh.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	DFS1(1, 0); Solve(1); DFS2(1, 0);
	printf("%lld\n", ans);
	return 0;
}

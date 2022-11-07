/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], anc[maxn][20], c[maxn];
bool vis[maxn]; LL ans = 0;
int f[2010][2010], g[2010][2010];
pii a[maxn], b[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val ) { ++ pos; for ( int i = pos; i < maxn; i += lowbit(i) ) c[i] += val; } 
inline int query(int pos) { int ret = 0; ++ pos; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS(v, u); anc[v][0] = u; 
	}
}

inline void DFS1(int u, int fa, int x)
{
	g[x][u] = fa;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u, x);
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 19; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; } 
	return anc[x][0];
}

inline int Get(int x, int y) { return g[x][y]; } 

inline int Solve(int x, int y)
{
	if ( f[x][y] != -1 ) return f[x][y];
	if ( vis[x] ) return f[x][y] = 1;
	f[x][y] = 0;
	for ( int i = Begin[x]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == y ) continue ; 
		if ( Solve(v, Get(v, y)) ) return f[x][y] = 1;
	}
	return 0;
}

inline void DFS3(int u, int fa, int x)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( vis[v] ) DFS3(v, u, dis[v]);
		else DFS3(v, u, x);
	}
	a[u] = pii(x, x + x - dis[u]);
	b[u] = pii(x, dis[u]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS(1, 0);
	REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];

	if ( m == 1 ) 
	{
		int u, v; scanf("%d%d", &u, &v);
		int t = LCA(u, v);
		if ( dis[u] + dis[v] - 2 * dis[t] <= 2 ) { puts("0"); return 0; }
		
		mem(anc); dis[u] = 1; DFS(u, 0);
		int sum = 1; vis[u] = true;
		while ( v != u ) { ++ sum; vis[v] = true; v = anc[v][0]; }

		DFS3(u, 0, 1);
		sort(a + 1, a + n + 1);
		for ( int l = 1, r; l <= n; l = r ) 
		{
			r = l;
			while ( r <= n && a[r].first == a[l].first ) 
			{
				modify(n + n + a[r].second, 1);
				++ r;
			}
			REP(i, l, r - 1) ans += query(n + n + a[i].second - 1);
		}

		mem(c);
		sort(b + 1, b + n + 1);
		for ( int l = 1, r; l <= n; l = r ) 
		{
			r = l;
			while ( r <= n && b[r].first == b[l].first ) ++ r;
			REP(i, l, r - 1) ans += query(b[i].second - 1);
			REP(i, l, r - 1) modify(b[i].second, 1);
		}

		cout << ans << endl;
		return 0;
	}

	REP(i, 1, n) DFS1(i, 0, i);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		int t = LCA(u, v);
		add(u, v); add(v, u);
		if ( dis[u] + dis[v] - 2 * dis[t] <= 2 ) continue ; 
		vis[u] = vis[v] = true;
	}

	memset(f, -1, sizeof(f));
	REP(i, 1, n) f[i][i] = 0;
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) 
		ans += Solve(i, j);
	printf("%lld\n", ans);
    return 0;
}

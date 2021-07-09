#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;
const int maxm = 2e6 + 10;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, m, q, k, N, d[maxn], w[maxn], Begin[maxm], Next[maxm], To[maxm], e, num[maxn], dis[maxn], anc[maxn][20];
int dfn[maxn], low[maxn], tot, Stack[maxn], cnt, now, ans, f[maxn], g[maxn], h[maxn], b[maxn];
vector<int> c[maxn], Edge[maxn];
map<int, int> Map[maxn];
bool vis[maxn];

inline void add(int u, int v) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
} 
inline void ADD(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); w[v] += w[u]; }

inline void Tarjan(int u)
{
	dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; 
		if ( !dfn[v] ) 
		{
			Tarjan(v); low[u] = min(low[u], low[v]);
			if ( low[v] == dfn[u] ) 
			{
				++ N; ADD(u, N); 
				while ( Stack[cnt] != v ) ADD(Stack[cnt --], N);
				ADD(v, N); -- cnt;
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

inline void DFS(int u, int fa)
{
	dfn[u] = ++ tot;
	for ( auto v : Edge[u] ) if ( v != fa ) 
	{
		dis[v] = dis[u] + 1; anc[v][0] = u;
		DFS(v, u);
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int i = 19; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
	if ( x == y ) return x;
	for ( int i = 19; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; } 
	return anc[x][0];
}

inline void DFS1(int u, int fa)
{
	if ( d[u] == now ) f[u] = 1; else f[u] = 0;
	for ( auto v : Edge[u] ) if ( v != fa ) { anc[v][0] = u; DFS1(v, u); f[u] = (f[u] + f[v]) % Mod; } 
	if ( vis[u] ) f[u] = (f[u] + f[u]) % Mod;
}

inline void DFS2(int u, int fa)
{
	if ( vis[fa] ) g[u] = (g[u] + g[u]) % Mod; if ( d[fa] == now ) ++ g[u]; 
	int sum = 0; for ( auto v : Edge[u] ) if ( v != fa ) sum = (sum + f[v]) % Mod;
	for ( auto v : Edge[u] ) if ( v != fa ) { g[v] = (g[u] + sum - f[v]) % Mod; DFS2(v, u); }
	b[u] = 0; for ( auto v : Edge[u] ) b[u] = (b[u] + (v == fa ? g[u] : f[v])) % Mod;
	h[u] = 1ll * b[u] * b[u] % Mod;	
	for ( auto v : Edge[u] ) h[u] = (h[u] - 1ll * (v == fa ? g[u] : f[v]) * (v == fa ? g[u] : f[v])) % Mod;
	h[u] = 1ll * h[u] * inv2 % Mod;
}

inline void DFS3(int u, int fa)
{
	for ( auto v : Edge[u] ) if ( v != fa ) DFS3(v, u);
	if ( u <= n ) 
	{
		int sum = 0; if ( d[u] == now ) ++ sum;
		for ( auto v : Edge[u] ) 
		{
			int x = v == fa ? g[u] : f[v];
			num[u] = (num[u] + 1ll * x * sum) % Mod; sum = (sum + x) % Mod;
		}
		for ( auto v : Edge[u] ) 
		{
			num[u] = (num[u] + h[v]) % Mod;
			if ( v == fa ) num[u] = (num[u] - 1ll * f[u] * (b[v] - f[u])) % Mod;
			else num[u] = (num[u] - 1ll * g[v] * (b[v] - g[v])) % Mod;
		}
	}
}

inline void Solve()
{
	ans = 0;
	REP(i, 1, k) 
	{ 
		now = i;
		DFS1(1, 0); g[1] = 0; DFS2(1, 0); DFS3(1, 0);
	}
}

inline void Build(int x)
{
	if ( !c[x].size() ) return ; 
	sort(c[x].begin(), c[x].end(), [](int a, int b) { return dfn[a] < dfn[b]; } );
	tot = 0; Stack[++ tot] = c[x][0]; Begin[c[x][0]] = 0;
	for ( auto it : c[x] ) if ( it != c[x][0] ) 
	{
		int t = LCA(it, Stack[tot]);	
		while ( dfn[Stack[tot - 1]] > dis[t] ) { add(Stack[tot - 1], Stack[tot]); -- tot; } 
		if ( Stack[tot - 1] != t ) { Begin[t] = 0; add(Stack[tot], t); Stack[tot] = t; } 
		else { add(Stack[tot - 1], Stack[tot]); -- tot; } 
		Begin[it] = 0; add(it, Stack[tot]); Stack[++ tot] = it;
	}
	while ( tot > 1 ) { add(Stack[tot - 1], Stack[tot]); -- tot; } 
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, n) { scanf("%d", &d[i]); c[d[i]].push_back(i); } 
	REP(i, 1, n) scanf("%d", &w[i]);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); ++ Map[u][v]; ++ Map[v][u]; } 
	N = n; Tarjan(1); REP(i, n + 1, N) if ( Edge[i].size() > 2 || Map[Edge[i][0]][Edge[i][1]] >= 2 ) vis[i] = true;

	dis[1] = 1; tot = 0; DFS(1, 0); REP(i, 1, N) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(i, 1, k)
	{
		Build(i);
	}

	REP(i, 1, n) ans = (ans + 1ll * w[i] * num[i]) % Mod; printf("%d\n", (ans + Mod) % Mod);
	scanf("%d", &q);
	REP(i, 1, q) { int x, y; scanf("%d%d", &x, &y); ans = (ans + 1ll * y * num[x]) % Mod; printf("%d\n", (ans + Mod) % Mod); }
	return 0;
}

/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 14时44分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 10007;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, ans1[maxn];
LL ans2[maxn];
int f[maxn], g[maxn], h[maxn], anc[1000010][20], size[maxn], dis[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 

inline void DFS(int u, int fa)
{
	f[u] = u; size[u] = 1; vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] ) continue ; 
		anc[v][0] = u; g[v] = u; dis[v] = dis[u] + 1;
		DFS(v, u); size[u] += size[v]; h[v] = size[v];
		ans1[u] += size[v]; ans2[u] += 1ll * size[v] * size[v];
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

inline void Merge(int x, int y)
{
	x = find(x); y = find(y); if ( x == y ) return ;
	if ( dis[g[x]] > dis[g[y]] ) swap(x, y);
	if ( g[x] == g[y] ) 
	{
		ans2[g[x]] += 1ll * (h[x] + h[y]) * (h[x] + h[y]) - 1ll * h[x] * h[x] - 1ll * h[y] * h[y];
		h[x] += h[y];
	}
	else { ans2[g[y]] -= 1ll * h[y] * h[y]; ans1[g[y]] -= h[y]; }
	f[y] = x;
}

inline void Insert(int x, int t) { while ( dis[g[find(f[x])]] > dis[t] ) Merge(x, g[find(f[x])]); }

inline void read(int &x)
{
	x = 0; char c = getchar();
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, m) { int u, v; read(u); read(v); add(u, v); add(v, u); } 
	dis[1] = 1; DFS(1, 0); REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(x, 1, n) for ( int i = Begin[x]; i; i = Next[i] ) 
	{
		int y = To[i]; if ( anc[x][0] == y || anc[y][0] == x || dis[x] < dis[y] ) continue ; 
		if ( find(x) == find(y) ) continue ; 
		int t = LCA(x, y); Insert(x, t); Insert(y, t); if ( x != t && y != t ) Merge(x, y);
	}
	while ( q -- ) 
	{
		int op, x, y; read(op);
		if ( op == 1 ) 
		{ 
			read(x); LL num = n - ans1[x] - 1;
			int ret = (ans2[x] + num * num) % Mod; printf("%d\n", ret);
		}
		else 
		{ 
			read(x); read(y); if ( find(x) == find(y) ) continue ; int t = LCA(x, y); 
			Insert(x, t); Insert(y, t); if ( x != t && y != t ) Merge(x, y);
		}
	}
    return 0;
}

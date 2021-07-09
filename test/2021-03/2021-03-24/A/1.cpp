#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 4e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], Root;
int Stack[maxn], tot, ans, m, g[maxn][2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void out(int x) { printf("%d\n", x); exit(0); } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS(v, u);
	}
}

inline void DFS1(int u, int fa)
{
	Stack[++ tot] = u;
	if ( (tot + 1) / 2 > dis[Root] ) { Root = Stack[(tot + 1) / 2]; ans = tot / 2; }
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS1(v, u);
	}
	-- tot;
}

inline void DFS3(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS3(To[i], u);
	if ( dis[u] == ans ) ++ g[m][0];
	if ( dis[u] == ans - 2 ) ++ g[m][1];
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, n + i); add(n + i, u); add(v, n + i); add(n + i, v); } 
	dis[1] = 1; DFS(1, 0); REP(i, 1, n + n - 1) if ( dis[i] > dis[Root] ) Root = i; 
	dis[Root] = 1; DFS1(Root, 0); dis[Root] = 1; DFS(Root, 0);
	for ( int i = Begin[Root]; i; i = Next[i] ) 
	{
		++ m; g[m][0] = g[m][1] = 0; DFS3(To[i], Root);
		if ( !g[m][0] ) { g[0][1] += g[m][1]; -- m; } 
	}
	if ( !(n & 1) ) 
	{
		if ( m == 3 && g[1][0] == 1 && g[2][0] == 1 && g[3][0] == 1 ) out(ans - 1);
		if ( m == 2 && ((g[1][0] == 1 && g[2][0] > 1) || (g[2][0] == 1 && g[1][0] > 1)) ) out(ans - 1);
	}
	if ( m == 2 && g[1][0] == 1 && g[2][0] == 1 ) 
	{
		if ( n & 1 ) out(ans - 1);
		if ( g[0][1] >= 2 ) out(ans - 1);
		if ( (g[1][1] >= 2 || g[2][1] >= 2) && g[0][1] ) out(ans - 1);
		if ( g[1][1] >= 2 && g[2][1] >= 2 ) out(ans - 1);
		out(ans - 2);
	}
	out(ans);
	return 0;
}

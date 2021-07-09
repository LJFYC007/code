/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期日 09时28分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], To[maxn], Next[maxn], e, f[maxn];
int dis[maxn], n, m, ans, anc[maxn][30], sum[maxn];

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void DFS(int u, int x)
{
	dis[u] = ++ x;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( dis[v] ) continue ;
		anc[v][0] = u;
		DFS(v, x);
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 20; j >= 0; -- j )
		if ( dis[anc[x][j]] >= dis[y] )
			x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 20; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] )
		{
			x = anc[x][j]; y = anc[y][j];
		}
	return anc[x][0];
}

inline void DFS1(int u, int fa)
{
	sum[u] = f[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; 
		if ( v == fa ) continue ;
		DFS1(v, u);
		sum[u] += sum[v];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1, 0);
	REP(j, 1, 20) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		++ f[u]; ++ f[v]; f[LCA(u, v)] -= 2;
	}
	DFS1(1, 0);
	REP(i, 2, n) if ( sum[i] == 0 ) ans += m; else if ( sum[i] == 1 ) ans ++;
	printf("%d\n", ans);
    return 0;
}

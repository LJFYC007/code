/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期五 08时37分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], anc[maxn][20], n, m, p[maxn][20];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void DFS(int u, int d)
{
	dis[u] = d;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( dis[v] ) continue ;
		anc[v][0] = u; p[v][0] = W[i];
		DFS(v, d + 1);
	}
}

inline int LCA(int x, int y)
{
	int ans = 0;
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 17; j >= 0; -- j )
		if ( dis[anc[x][j]] >= dis[y] ) { ans += p[x][j]; x = anc[x][j]; }
	if ( x == y ) return ans;
	for ( int j = 17; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] ) 
		{
			ans += p[x][j] + p[y][j];
			x = anc[x][j];
			y = anc[y][j];
		}
	return ans + p[x][0] + p[y][0];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
	DFS(1, 1);
	REP(j, 1, 17)
		REP(i, 1, n)
		{
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
			p[i][j] = p[i][j - 1] + p[anc[i][j - 1]][j - 1];
		}
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		printf("%d\n", LCA(u, v));
	}
    return 0;
}

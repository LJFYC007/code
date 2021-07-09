/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月31日 星期五 08时37分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], anc[maxn][20], n, m;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void DFS(int u, int d)
{
	dis[u] = d;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( dis[v] ) continue ;
		anc[v][0] = u;
		DFS(v, d + 1);
	}
}

inline int LCA(int x, int y)
{
	int ans = 0;
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 17; j >= 0; -- j )
		if ( dis[anc[x][j]] >= dis[y] ) { x = anc[x][j]; ans += 1 << j; }
	if ( x == y ) return ans;
	for ( int j = 17; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] ) 
		{
			ans += 1 << (j + 1);
			x = anc[x][j];
			y = anc[y][j];
		}
	return ans + 2;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1, 1);
	REP(j, 1, 17)
		REP(i, 1, n)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	scanf("%d", &m);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		printf("%d\n", LCA(u, v));
	}
    return 0;
}

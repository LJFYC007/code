/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期日 15时50分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 800010;

int Begin[maxn], Next[maxn], To[maxn], e, Max;
int dis[maxn], n, m, anc[maxn][20], root;

inline void add(int u, int v)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
}

inline void DFS(int u, int x)
{
	dis[u] = ++ x;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( dis[v] ) continue ;
		anc[v][0] = u; DFS(v, x);
	}
}

inline int LCA(int x, int y)
{
	if ( x == root ) return x;
	if ( y == root ) return y;
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
//	printf("%d %d\n", x, y);
	if ( x == y ) return x;
	for ( int j = 18; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] ) 
		{
			x = anc[x][j];
			y = anc[y][j];
		}
	return anc[x][0];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); 
	REP(i, 1, n)
	{
		int u, v; scanf("%d%d", &u, &v); Max = max(Max, max(u, v));
		if ( v == -1 ) { root = u; continue ; }
		add(u, v); add(v, u);
	}
	DFS(root, 0);
	REP(j, 1, 18) REP(i, 1, Max) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	scanf("%d", &m);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		int x = LCA(u, v);
	//	printf("%d %d %d\n", u, v, x);
		if ( x == u ) puts("1");
		else if ( x == v ) puts("2");
		else puts("0");
	}
    return 0;
}

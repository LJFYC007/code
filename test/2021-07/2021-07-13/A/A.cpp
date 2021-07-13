/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 08时57分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], f[maxn], g[maxn], anc[maxn], deg[maxn];
int Begin[maxn], Next[maxn << 1], To[maxn << 1], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		anc[v] = u; DFS(v, u);
	}
	int Max = 0, Maxx = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) 
	{
		if ( f[To[i]] > Max ) { Maxx = Max; Max = f[To[i]]; }
		else Maxx = max(Maxx, f[To[i]]);
	}
	f[u] = max(Maxx, a[u]);
}

inline void DFS1(int u, int fa)
{
	int Max = g[u], Maxx = 0, Maxxx = 0, posx = -1, posy = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) 
	{
		if ( f[To[i]] > Max ) { Maxxx = Maxx; Maxx = Max; Max = f[To[i]]; posy = posx; posx = To[i]; }
		else if ( f[To[i]] > Maxx ) { Maxxx = Maxx; Maxx = f[To[i]]; posy = To[i]; }
		else Maxxx = max(Maxxx, f[To[i]]);
	}
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa )
	{
		int v = To[i];
		if ( v == posx || v == posy ) g[v] = max(a[u], Maxxx);
		else g[v] = max(a[u], Maxx);
		DFS1(v, u);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	DFS(1, 0); DFS1(1, 0);
	REP(i, 1, n) 
	{
		int ans = max(a[i], g[i]);
		for ( int j = Begin[i]; j; j = Next[j] ) if ( To[j] != anc[i] ) 
			ans = max(ans, f[To[j]]);
		printf("%d ", ans);
	}
    return 0;
}

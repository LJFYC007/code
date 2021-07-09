/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 20时47分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	g[u] = m; f[u] = 0; int Max = -m - 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u); f[u] += f[v]; 
		Max = max(Max, g[v] - m - 1);
		g[u] = min(g[u], g[v] - 1);
	}
	if ( m - g[u] <= Max - 1 ) g[u] = Max + m;

	if ( g[u] <= 0 ) 
	{
		g[u] = m + m + 1;
		++ f[u];
	}
}

inline bool Check(int x) { m = x; DFS(1, 0); return f[1] + (g[1] <= m) <= k; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	int l = 0, r = n, ans = 0;
	while ( l <= r ) 
	{
		int Mid = l + r >> 1;
		if ( Check(Mid) ) { ans = Mid; r = Mid - 1; } 
		else l = Mid + 1;
	}
	printf("%d\n", ans);
    return 0;
}

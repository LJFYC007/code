/***************************************************************
	File name: ARC097F.cpp
	Author: ljfcnyali
	Create time: 2021年06月18日 星期五 09时48分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, deg[maxn], ans, sum = -2, val[maxn], f[maxn];
bool vis[maxn], col[maxn]; queue<int> Q;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; } 

inline void DFS(int u, int fa)
{
	f[u] = val[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( !vis[v] || v == fa ) continue ; 
		DFS(v, u); 
		ans = max(ans, f[u] + f[v]);
		f[u] = max(f[u], f[v] + val[u]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	getchar(); REP(i, 1, n) { char c = getchar(); col[i] = c == 'W'; }
	memset(vis, true, sizeof(vis));
	REP(i, 1, n) if ( deg[i] == 1 ) Q.push(i);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		if ( col[u] ) continue ; vis[u] = false;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; -- deg[v];
			if ( deg[v] == 1 ) Q.push(v);
		}
	}
	int Root = 0; 
	REP(i, 1, n) if ( vis[i] ) 
	{ 
		sum += 2; Root = i; 
		if ( (deg[i] + col[i]) % 2 != 0 ) { val[i] = 2; ++ sum; }
	} 
	if ( Root == 0 ) { puts("0"); return 0; } 
	DFS(Root, 0);
	printf("%d\n", sum - ans);
    return 0;
}

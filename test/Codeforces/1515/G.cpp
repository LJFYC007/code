/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2021年05月06日 星期四 10时22分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], tot;
int dfn[maxn], low[maxn], Stack[maxn], cnt, p[maxn], ans[maxn], N, dis[maxn];
bool vis[maxn]; vector<pii> Edge[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Tarjan(int u)
{
	dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
		else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
	}
	if ( dfn[u] == low[u] ) 
	{
		++ N; p[u] = N;
		while ( Stack[cnt] != u ) p[Stack[cnt --]] = N;
		-- cnt;
	}
}

inline void DFS(int u)
{
	vis[u] = true;
	for ( auto v : Edge[u] ) 
		if ( !vis[v.first] ) { dis[v.first] = dis[u] + v.second; DFS(v.first); }
		else cnt = __gcd(cnt, dis[u] - dis[v.first] + v.second);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); } 
	REP(i, 1, n) if ( !dfn[i] ) Tarjan(i);
	REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( p[u] != p[v] ) continue ;
		Edge[u].push_back(pii(v, W[i]));
	}
	REP(i, 1, n) if ( !vis[i] ) { cnt = 0; DFS(i); ans[p[i]] = cnt; } 
	scanf("%lld", &q);
	while ( q -- ) 
	{
		int v, s, t; scanf("%lld%lld%lld", &v, &s, &t);
		int x = __gcd(t, ans[p[v]]);
		if ( (t - s) % x == 0 ) puts("YES"); else puts("NO");
	}
    return 0;
}

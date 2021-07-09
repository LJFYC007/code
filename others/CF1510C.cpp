/***************************************************************
	File name: CF1510C.cpp
	Author: ljfcnyali
	Create time: 2021年06月18日 星期五 21时47分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dfn[maxn], low[maxn], tot;
int Stack[maxn], cnt, deg[maxn], ban[maxn]; vector<pii> ans;
bool vis[maxn], use[maxn]; vector<int> Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void Tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) 
		{ 
			Tarjan(v, u); low[u] = min(low[u], low[v]); 
			if ( low[v] == dfn[u] ) 
			{
				if ( Stack[cnt] == v ) { Edge[u].push_back(v); Edge[v].push_back(u); ++ deg[u]; ++ deg[v]; }
				while ( Stack[cnt] != v ) -- cnt; -- cnt;
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

inline void DFS(int u, int fa)
{
	vis[u] = true;
	for ( auto v : Edge[u] ) if ( v != fa ) DFS(v, u);
	if ( deg[u] % 2 == 1 && deg[fa] % 2 == 1 && !use[u] && !use[fa] ) 
	{
		use[u] = use[fa] = true;
		ban[u] = fa; ban[fa] = u;
	}
}

inline int DFS1(int u, int fa)
{
	vis[u] = true; int lst = 0;
	for ( auto v : Edge[u] ) if ( v != fa && v != ban[u] ) 
	{
		int x = DFS1(v, u);
		if ( lst ) { ans.push_back(pii(lst, x)); lst = 0; }
		else lst = x;
	}
	if ( lst ) return lst; return u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( ~scanf("%d%d", &n, &m) )
	{
		if ( !n ) return 0;
		e = 1; tot = cnt = 0; ans.clear();
		REP(i, 1, n) 
		{
			Begin[i] = dfn[i] = low[i] = vis[i] = use[i] = deg[i] = ban[i] = 0;
			Edge[i].clear(); 
		}
		REP(i, 1, m)
		{
			int k, x, y; scanf("%d%d", &k, &x);
			REP(j, 2, k) { scanf("%d", &y); add(x, y); add(y, x); x = y; }
		}
		Tarjan(1, 0);
		
		REP(i, 1, n) if ( !vis[i] ) DFS(i, 0);
		REP(i, 1, n) vis[i] = false;
		REP(i, 1, n) if ( !vis[i] ) 
		{
			int x = DFS1(i, 0);
			if ( x != i ) ans.push_back(pii(x, i));
		}
		printf("%zu\n", ans.size());
		for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
	}
    return 0;
}

/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月20日 星期一 10时47分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, k;
int low[maxn], dfn[maxn], n, p[maxn], sum[maxn], money[maxn], degree[maxn];
int ans, tot;
bool vis[maxn];
stack<int> Stack;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void dfs(int u)
{
	vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( vis[v] ) continue ;
		dfs(v);
	}
}

inline void Tarjan(int u, int x)
{
	dfn[u] = low[u] = ++ x; //vis[u] = true;
	Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v, x); low[u] = min(low[u], low[v]); }
		else if ( !p[v] ) low[u] = min(low[u], dfn[v]); 
	}
	if ( dfn[u] == low[u] )
	{
		p[u] = ++ tot; sum[tot] = money[u];
		while ( u != Stack.top() ) 
		{
			p[Stack.top()] = tot; sum[tot] = min(sum[tot], money[Stack.top()]);
			Stack.pop();
		}
		Stack.pop();
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) money[i] = INF;
	REP(i, 1, k) { int x; scanf("%d", &x); scanf("%d", &money[x]); }
	scanf("%d", &k);
	REP(i, 1, k) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
	REP(i, 1, n) if ( money[i] != INF ) dfs(i);
	REP(i, 1, n) if ( money[i] == INF && !vis[i] ) { printf("NO\n%d\n", i); return 0; }
	mem(vis);
	REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( p[u] != p[v] ) degree[p[v]] ++;
		}
//	REP(i, 1, tot) printf("%d ", money[i]);
	REP(i, 1, tot) if ( degree[i] == 0 ) ans += sum[i];
	printf("YES\n%d\n", ans);
    return 0;
}

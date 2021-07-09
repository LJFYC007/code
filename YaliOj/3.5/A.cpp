/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月18日 星期六 10时22分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, sum[maxn], low[maxn], dfn[maxn], tot;
int p[maxn], ans, k, degree[maxn];
bool vis[maxn];

stack<int> Stack;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void Tarjan(int u, int x)
{
	low[u] = dfn[u] = ++ x; vis[u] = true;
	Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v, x); low[u] = min(low[u], low[v]); }
		else if ( vis[v] ) low[u] = min(low[u], dfn[v]); 
	}
	if ( low[u] == dfn[u] ) 
	{
		p[u] = ++ tot; sum[tot] = 1;	
		while ( Stack.top() != u ) 
		{
			p[Stack.top()] = tot; ++ sum[tot];
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
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		add(u, v);
	}
	REP(i, 1, n) if ( !vis[i] ) Tarjan(i, 0);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( p[u] != p[v] ) ++ degree[p[u]];
		}
//	REP(i, 1, tot) printf("%d ", sum[i]);
//	REP(i, 1, tot) printf("%d ", degree[i]);
	REP(i, 1, tot) 
		if ( degree[i] == 0 ) 
		{ 
			if ( ans ) { printf("0\n"); return 0; }
			ans = sum[i];
		}
	printf("%d\n", ans);
    return 0;
}

/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月20日 星期一 10时38分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, w[maxn], degree[maxn];
int low[maxn], dfn[maxn], n, sum[maxn], p[maxn], tot;
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
	dfn[u] = low[u] = ++ x; vis[u] = true;
	Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v, x); dfn[u] = min(dfn[u], dfn[v]); }
		else if ( vis[v] ) dfn[u] = min(dfn[u], low[v]);
	}
	if ( dfn[u] == low[u] ) 
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
	scanf("%d", &n);
	REP(i, 1, n)
		REP(j, 1, n)
		{
			int x; scanf("%d", &x);
			if ( x == 1 ) add(i, j);
		}
	REP(i, 1, n) if ( !vis[i] ) Tarjan(i, 0);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( p[u] != p[v] ) ++ degree[p[v]];
		}
	int ans = 0;
	REP(i, 1, tot) if ( degree[i] == 0 ) ++ ans;
	printf("%d\n", ans);
    return 0;
}

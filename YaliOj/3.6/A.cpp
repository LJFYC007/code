/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月21日 星期二 09时35分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, be[maxn], cnt;
int low[maxn], dfn[maxn], n, m, p[maxn], ans, tot, degree[maxn];
bool vis[maxn];
stack<int> Stack;

inline void add(int u, int v)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; be[e] = e + 1;
	To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; be[e] = e - 1;
}

inline void Tarjan(int u)
{
	low[u] = dfn[u] = ++ cnt; Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		vis[i] = true;
		if ( !vis[be[i]] ) 
		{
			int v = To[i];
			if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
			else low[u] = min(low[u], dfn[v]);
		}
	}
	if ( low[u] == dfn[u] ) 
	{
		p[u] = ++ tot;
		while ( Stack.top() != u ) 
		{
			p[Stack.top()] = tot; Stack.pop();
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
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
	Tarjan(1);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			vis[i] = false;
			if ( vis[be[i]] ) 
			{
				int v = To[i];
				if ( p[u] != p[v] ) { ++ degree[p[u]]; ++ degree[p[v]]; }
			}
		}
	REP(i, 1, tot) if ( degree[i] == 1 ) ++ ans;
	printf("%d\n", (ans + 1) / 2);
    return 0;
}

/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月20日 星期一 10时21分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int Begin[maxn], Next[maxn], To[maxn], e;
int low[maxn], dfn[maxn], n, p[maxn], sum[maxn], tot;
int degree1[maxn], degree2[maxn], ans1, ans2;
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
			p[Stack.top()] = tot; Stack.pop();
			++ sum[tot];
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
	{
		int x;
		while ( 1 ) 
		{
			scanf("%d", &x);
			if ( x == 0 ) break ; 
			add(i, x);
		}
	}
	REP(i, 1, n) if ( !vis[i] ) Tarjan(i, 0);
	if ( tot == 1 ) { printf("1\n0\n"); return 0; } 
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( p[u] != p[v] ) ++ degree1[p[u]], ++ degree2[p[v]];
		}
	REP(i, 1, tot)
	{
		if ( degree1[i] == 0 ) ++ ans1;
		if ( degree2[i] == 0 ) ++ ans2;
	}	
	printf("%d\n%d\n", ans2, max(ans1, ans2));
    return 0;
}

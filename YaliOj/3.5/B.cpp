/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月20日 星期一 08时37分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int Begin1[maxn], To1[maxn], Next1[maxn], e1;
int Begin2[maxn], To2[maxn], Next2[maxn], e2;
int sum[maxn], p[maxn], n, m, Mod, dfn[maxn], low[maxn], tot;
int degree[maxn], num[maxn], Max[maxn];
bool vis[maxn];
stack<int> Stack;

inline void add1(int u, int v)
{
	To1[++ e1] = v;
	Next1[e1] = Begin1[u];
	Begin1[u] = e1;
}

inline void add2(int u, int v)
{
	To2[++ e2] = v;
	Next2[e2] = Begin2[u];
	Begin2[u] = e2;
}

inline void Tarjan(int u, int x)
{
	low[u] = dfn[u] = ++ x;
	vis[u] = true; Stack.push(u);
	for ( int i = Begin1[u]; i; i = Next1[i] )
	{
		int v = To1[i];
		if ( !dfn[v] ) { Tarjan(v, x); dfn[u] = min(dfn[u], dfn[v]); }
		else if ( vis[v] ) { dfn[u] = min(dfn[u], low[v]); }
	}
	if ( low[u] == dfn[u] ) 
	{
		p[u] = ++ tot; sum[tot] ++;
		while ( Stack.top() != u ) 
		{
			p[Stack.top()] = tot;
			sum[tot] ++;
			Stack.pop();
		}
		Stack.pop();
	}
}

inline void DFS(int u, int s)
{
	if ( s > Max[u] ) { Max[u] = s; num[u] = 1; }
	else if ( s == Max[u] ) { ++ num[u]; num[u] %= Mod; }
	else if ( vis[u] == true ) return ;
	vis[u] = true;
	for ( int i = Begin2[u]; i; i = Next2[i] ) 
	{
		int v = To2[i];
		DFS(v, s + sum[v]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Mod);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		add1(u, v);
	}
	REP(i, 1, n) if ( !vis[i] ) Tarjan(i, 0);
	REP(u, 1, n)
		for ( int i = Begin1[u]; i; i = Next1[i] )
		{
			int v = To1[i];
			if ( p[u] != p[v] ) { add2(p[u], p[v]); ++ degree[p[v]]; }
		}
	mem(vis);
	REP(i, 1, tot) if ( degree[i] == 0 ) DFS(i, sum[i]);
	int Maxx = 0, ans = 0;
	REP(i, 1, tot) 
		if ( Max[i] > Maxx ) { Maxx = Max[i]; ans = num[i]; } 
		else if ( Max[i] == Maxx ) ans += num[i];
	printf("%d\n%d\n", Maxx, ans);
    return 0;
}

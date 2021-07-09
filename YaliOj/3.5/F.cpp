/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月20日 星期一 14时45分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10000010;

int Begin[maxn], Next[maxn], To[maxn], e, w[maxn];
int low[maxn], dfn[maxn], n, m, s, p[maxn], sum[maxn], tot, k, num;
int dis[maxn], ans;
int Begin1[maxn], Next1[maxn], To1[maxn], e1;
bool vis[maxn];
stack<int> Stack;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void add1(int u, int v)
{
//	printf("%d %d\n", u, v);
	To1[++ e1] = v;
	Next1[e1] = Begin1[u];
	Begin1[u] = e1;
}

//int cnt;

inline void Tarjan(int u)
{
//	++ cnt;
//	if ( cnt == 1000) exit(0);
	low[u] = dfn[u] = ++ num;// vis[u] = true;
	Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
		else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
	}
	if ( low[u] == dfn[u] )
	{
		p[u] = ++ tot; sum[tot] = w[u];
//		cerr << tot << " " << u << endl;
//		printf("%d %d ", tot, u);
		while ( Stack.top() != u ) 
		{
//			printf("%d ", Stack.top());
			p[Stack.top()] = tot; sum[tot] += w[Stack.top()];
			Stack.pop();
		}
//		puts("");
		Stack.pop();
	}
}

inline void Solve()
{
	memset ( dis, 0, sizeof ( dis ) );
	dis[p[s]] = sum[p[s]];
	queue<int> Q; Q.push(p[s]);
//	mem(vis);
	while ( !Q.empty() ) 
	{
//		++ cnt;
//		if ( cnt == 1000 ) return ;
		int u = Q.front(); Q.pop();
		vis[u] = false;
		for ( int i = Begin1[u]; i; i = Next1[i] )
		{
			int v = To1[i];
			if ( dis[v] < dis[u] + sum[v] ) 
			{
				dis[v] = dis[u] + sum[v];
				if ( !vis[v] ) 
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
//	REP(i, 1, tot) printf("%d ", dis[i]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
	REP(i, 1, n) scanf("%d", &w[i]);
	REP(i, 1, n) if ( !dfn[i] ) Tarjan(i);
	scanf("%d%d", &s, &k);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i];
			if ( p[u] != p[v] ) add1(p[u], p[v]);
		}
	Solve();
	REP(i, 1, k) { int x; scanf("%d", &x); ans = max(ans, dis[p[x]]); }
	printf("%d\n", ans);
    return 0;
}

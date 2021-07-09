/***************************************************************
	File name: AGC038F.cpp
	Author: ljfcnyali
	Create time: 2021年01月28日 星期四 08时53分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, k, a[maxn], b[maxn], p[maxn], q[maxn], ans, Begin[maxn], To[maxn], Next[maxn], W[maxn];
int e = 1, dis[maxn], S, T;
map<int, int> Map[maxn];

inline void add(int u, int v, int w) { Map[u][v] += w; }

inline bool BFS(int s, int t)
{
	queue<int> Q; Q.push(s); REP(i, 1, t) dis[i] = 0; dis[s] = 1;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i]; if ( dis[v] || !W[i] ) continue ;
			dis[v] = dis[u] + 1;
			if ( v == t ) return true;
			Q.push(v);
		}
	}
	return false;
}

inline int DFS(int u, int t, int flow)
{
	if ( u == t || !flow ) return flow;
	int f = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ;
		int x = DFS(v, t, min(flow, W[i]));
		flow -= x; f += x;
		W[i] -= x; W[i ^ 1] += x;
	}
	if ( !f ) dis[u] = 0;
	return f;
}

inline int Solve(int s, int t)
{
	int Maxflow = 0;
	while ( BFS(s, t) )
		while ( int flow = DFS(s, t, INF) )
			Maxflow += flow;
	return Maxflow;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); ++ a[i]; }
	REP(i, 1, n) { scanf("%d", &b[i]); ++ b[i]; }
	REP(i, 1, n) if ( !p[i] ) 
	{
		++ m; int x = i;
		while ( !p[a[x]] ) { p[a[x]] = m; x = a[x]; }
	}
	REP(i, 1, n) if ( !q[i] ) 
	{
		++ m; int x = i;
		while ( !q[b[x]] ) { q[b[x]] = m; x = b[x]; }
	}
	ans = n; S = m + 1; T = m + 2;
	REP(i, 1, n) 
		if ( a[i] == i && b[i] == i ) -- ans;		
		else if ( a[i] == i && b[i] != i ) add(q[i], T, 1);
		else if ( a[i] != i && b[i] == i ) add(S, p[i], 1);
		else if ( a[i] == b[i] ) { add(p[i], q[i], 1); add(q[i], p[i], 1); }
		else add(q[i], p[i], 1);
	REP(i, 1, m + 2) for ( auto it : Map[i] ) 
	{
		int u = i, v = it.first, w = it.second;
		To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;	W[e] = w;
		swap(u, v); w = 0;
		To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;	W[e] = w;
	}
	printf("%d\n", ans - Solve(S, T));
    return 0;
}

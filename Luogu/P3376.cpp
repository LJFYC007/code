/***************************************************************
	File name: P3376.cpp
	Author: ljfcnyali
	Create time: 2021年04月09日 星期五 09时21分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, m, s, t, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], dis[maxn];

inline void add(int u, int v, int w) 
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
	swap(u, v); w = 0;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
}

inline bool BFS()
{
	queue<int> Q; Q.push(s); mem(dis); dis[s] = 1;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( !W[i] || dis[v] ) continue ; 
			dis[v] = dis[u] + 1; Q.push(v);
		}
	}
	return dis[t];
}

inline int DFS(int u, int flow)
{
	int f = 0; if ( !flow || u == t ) return flow;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( !W[i] || dis[v] != dis[u] + 1 ) continue ; 
		int x = DFS(v, min(flow, W[i]));
		if ( x ) { flow -= x; f += x; W[i] -= x; W[i ^ 1] += x; } 
	}
	dis[u] = 0; return f;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); }
	int flow = 0; while ( BFS() ) flow += DFS(s, INF);
	printf("%lld\n", flow);
    return 0;
}

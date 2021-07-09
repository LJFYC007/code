/***************************************************************
	File name: MCMF.cpp
	Author: ljfcnyali
	Create time: 2021年02月04日 星期四 16时24分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 2147483647;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, s, t, W[maxn], F[maxn];
int dis[maxn], pre[maxn], a[maxn], flow, cost, pos[maxn];
bool vis[maxn];
queue<int> Q;

inline void add(int u, int v, int w, int f)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
	swap(u, v); w = 0; f = -f;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
}

inline bool BFS()
{
	REP(i, 1, n) dis[i] = INF; dis[s] = 0; a[s] = INF; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( !W[i] ) continue ; 
			if ( dis[v] > dis[u] + F[i] ) 
			{
				dis[v] = dis[u] + F[i]; pre[v] = i; pos[v] = u;
				a[v] = min(a[u], W[i]);
				if ( !vis[v] ) { vis[v] = true; Q.push(v); }
			}
		}
		vis[u] = false;
	}
	return dis[t] != INF;
}

inline void Solve()
{
	int x = t; flow += a[t]; cost += dis[t] * a[t];
	while ( x != s ) 
	{
		W[pre[x]] -= a[t]; W[pre[x] ^ 1] += a[t];
		x = pos[x];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &s, &t);
	REP(i, 1, m) { int u, v, w, f; scanf("%d%d%d%d", &u, &v, &w, &f); add(u, v, w, f); } 
	while ( BFS() ) Solve();
	printf("%d %d\n", flow, cost);
    return 0;
}

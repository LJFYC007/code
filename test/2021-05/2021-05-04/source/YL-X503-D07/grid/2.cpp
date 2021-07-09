#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int INF = 0x3f3f3f3f;
const int maxn = 210;
const int maxN = maxn * maxn;
const int maxm = 3 * maxn * maxn * maxn;

int n, m, ans[maxn][maxn], Begin[maxN], Next[maxm], To[maxm], e = 1, W[maxm];
int dis[maxN], s, t;
bool vis[maxN];

inline void add(int u, int v, int w)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
	swap(u, v); w = 0;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

inline int id(int x, int y) { return (x - 1) * m + y; } 

inline bool BFS()
{
	mem(dis); dis[s] = 1; queue<int> Q; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( dis[v] || !W[i] ) continue ; 
			dis[v] = dis[u] + 1; Q.push(v);
		}
	}
	return dis[t];
}

inline int DFS(int u, int flow)
{
	if ( u == t || !flow ) return flow;
	int f = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ; 
		int x = DFS(v, min(flow, W[i]));	
		if ( x ) { flow -= x; f += x; W[i] -= x; W[i ^ 1] += x; } 
	}
	dis[u] = 0; return f;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, n) { REP(j, 1, n) printf("%d ", (i + j - 2) % n + 1); puts(""); }
	return 0;
	s = n * m * 2 + n + n + 1; t = s + 1;
	REP(i, 1, n) { add(s, n * m * 2 + i, n); add(n * m * 2 + n + i, t, n); }
	REP(i, 1, n) REP(j, 1, m) { add(n * m * 2 + i, id(i, j), 1); add(id(n + i, j), n * m * 2 + n + i, 1); }
	REP(i, 1, n) REP(j, 1, n) 
	{
		REP(k, 1, m - n) { int x; scanf("%d", &x); vis[x] = true; }
		REP(k, 1, m) 
		{
			if ( !vis[k] ) add(id(i, k), id(n + j, k), 1);
			vis[k] = false;
		}
	}
	int flow = 0; while ( BFS() ) flow += DFS(s, INF);
	if ( flow != n * n ) { puts("NO"); return 0; } 
	REP(i, 1, n * m) for ( int j = Begin[i]; j; j = Next[j] ) if ( !W[j] )
	{
		int v = To[j];	
		if ( v <= n * m * 2 ) 
		{
		cerr << i << " " << v << endl;
		cerr << (i - 1) / m + 1 << " " << (v - 1) / m + 1 - n << " " << (i - 1) % m + 1 << endl;
		ans[(i - 1) / m + 1][(v - 1) / m + 1 - n] = (i - 1) % m + 1;
		}
	}
	REP(i, 1, n) { REP(j, 1, n) printf("%d ", ans[i][j]); puts(""); } 
	return 0;
}

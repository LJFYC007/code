#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>
#define mem(a) memset((a), 0, sizeof(a))

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, lim, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int id[maxn], s, t, dis[maxn];
pii Edge[maxn];

inline void add(int u ,int v, int w) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
	swap(u, v); w = 0;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

inline bool BFS(int s, int t)
{
	mem(dis); dis[s] = 1; queue<int> Q; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) if ( W[i] ) 
		{
			int v = To[i];
			if ( !dis[v] ) { dis[v] = dis[u] + 1; Q.push(v); }
		}
	}
	return dis[t] != 0;
}

inline int DFS(int u, int t, int flow)
{
	if ( u == t || !flow ) return flow;
	int f = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( !W[i] || dis[v] != dis[u] + 1 ) continue ;
		int x = DFS(v, t, min(flow, W[i]));
		if ( x )
		{
			flow -= x; f += x;
			W[i] -= x; W[i ^ 1] += x;
		}
	}
	if ( !f ) dis[u] = 0; return f;
}

int main()
{
    freopen("socialbutterfly.in", "r", stdin);
    freopen("socialbutterfly.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &lim); 
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[i] = pii(u, v); }
	e = 1; s = n + m + 1; t = n + m + 2;
	REP(i, 1, m)
	{
		add(s, i, 1);
		add(i, m + Edge[i].first, INF);
		add(i, m + Edge[i].second, INF);
	}
	REP(i, 1, n) { id[i] = e + 1; add(m + i, t, lim); }
	int ans = m; while ( BFS(s, t) ) ans -= DFS(s, t, INF);
    REP(o, 1, n)
    {
		int x = W[id[o] ^ 1];
		W[id[o]] = W[id[o] ^ 1] = 0;
		while ( BFS(m + o, s) && x ) { int w = DFS(m + o, s, x); x -= w; ans += w; } 
		while ( BFS(s, t) ) ans -= DFS(s, t, INF);
		W[id[o]] = lim;
		if ( ans > 0 ) { puts("Yes"); return 0; } 
    }
    puts("No");
    return 0;
}

/***************************************************************
	File name: AGC029F.cpp
	Author: ljfcnyali
	Create time: 2021年04月04日 星期日 21时35分27秒
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

int n, s, t, e = 1, Begin[maxn], Next[maxn], To[maxn], W[maxn], dis[maxn], p[maxn];
pii ans[maxn];
vector<int> b[maxn];
bool vis[maxn];

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
			int v = To[i];
			if ( W[i] && !dis[v] ) { dis[v] = dis[u] + 1; Q.push(v); } 
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
		int v = To[i]; if ( !W[i] || dis[v] != dis[u] + 1 ) continue ; 
		int x = DFS(v, min(flow, W[i]));
		if ( x ) { flow -= x; f += x; W[i] -= x; W[i ^ 1] += x; }
	}
	dis[u] = 0; return f;
}

queue<pii> Q;
inline void Insert(int x)
{
	for ( auto it : b[x] ) if ( !vis[it] ) { vis[it] = true; Q.push(pii(it, x)); } 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); s = n + n; t = s + 1;
	REP(i, 1, n) add(i, t, 1);
	REP(i, 1, n - 1)
	{
		int x; scanf("%d", &x); add(s, n + i, 1);
		REP(j, 1, x) 
		{ 
			int y; scanf("%d", &y); 
			if ( y != 1 ) add(n + i, y, 1);
			b[y].push_back(i); 
		}
	}
	int flow = 0; while ( BFS() ) flow += DFS(s, INF);
	if ( flow != n - 1 ) { puts("-1"); return 0; } 
	REP(i, n + 1, n + n - 1) for ( int j = Begin[i]; j; j = Next[j] ) if ( !W[j] ) p[i - n] = To[j];
	// REP(i, 1, n - 1) cout << p[i] << " "; cout << endl;
	Insert(1); int num = 0;
	while ( !Q.empty() ) 
	{
		pii u = Q.front(); Q.pop(); ++ num;
		Insert(p[u.first]); ans[u.first] = pii(p[u.first], u.second);
	}
	if ( num != n - 1 ) puts("-1");
	else REP(i, 1, n - 1) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}

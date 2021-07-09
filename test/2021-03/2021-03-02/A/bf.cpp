#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 6e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, num;
bool cut[maxn], vis[maxn];
vector<pii> Edge;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	vis[u] = true; ++ num;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] || cut[v] ) continue ; 
		DFS(v);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge.push_back(pii(u, v)); add(u, v); add(v, u); } 
	REP(i, 1, m)
	{
		int u = Edge[i - 1].first, v = Edge[i - 1].second; cut[u] = cut[v] = true;
		REP(j, 1, n) vis[j] = false;
		num = 0; REP(j, 1, n) if ( !cut[j] ) { DFS(j); break ; } 
		if ( num == n - 2 ) printf("0");
		else printf("1");
		cut[u] = cut[v] = false;
	}
	puts("");
	return 0;
}

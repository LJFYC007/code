#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, a[maxn], deg[maxn];
vector<pii> Edge;
vector<int> E[maxn];
bool vis[maxn], use[maxn];

inline void DFS(int x)
{
	if ( x == n + 1 ) 
	{
		REP(i, 1, n - 1) vis[i] = false;
		REP(i, 0, n - 2) vis[abs(a[Edge[i].first] - a[Edge[i].second])] = true;
		REP(i, 1, n - 1) if ( !vis[i] ) return ; 
		puts("Yes"); REP(i, 1, n) printf("%d ", a[i]); puts("");
		exit(0); return ; 
	}
	REP(i, 1, n) if ( !use[i] ) { use[i] = true; a[x] = i; DFS(x + 1); use[i] = false; } 
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("dandelion.in", "r", stdin);
	freopen("dandelion.out", "w", stdout);
#endif
	scanf("%d", &n); 
	REP(i, 1, n - 1) 
	{ 
		int u, v; scanf("%d%d", &u, &v); Edge.push_back(pii(u, v)); 
		E[u].push_back(v); E[v].push_back(u);
		++ deg[u]; ++ deg[v]; 
	} 
	if ( n <= 10 ) { DFS(1); puts("No"); }

	int x = 0, y = 0;
	REP(i, 1, n) if ( deg[i] != 1 ) 
	{
		if ( !x ) x = i;
		else if ( !y ) y = i;
	}
	a[x] = n; 
	int now = 0;
	for ( auto it : E[x] ) if ( it != y ) a[it] = ++ now;
	a[y] = ++ now;
	for ( auto it : E[y] ) if ( it != x ) a[it] = ++ now;
	puts("Yes"); REP(i, 1, n) printf("%d ", a[i]); puts("");
	return 0;
}

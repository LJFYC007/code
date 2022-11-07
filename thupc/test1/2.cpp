/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, vis[maxn], cnt;
struct node { int u, v, w; } ; vector<node> ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline bool DFS(int u, int fa)
{
	cerr << u << endl;
	vector<int> a; if ( fa ) a.push_back(fa); 
	vis[u] = ++ cnt;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] && vis[v] < vis[u] ) continue ; 
		if ( vis[v] > vis[u] || !DFS(v, u) ) a.push_back(v);
	}
	while ( a.size() >= 2 ) 
	{
		int x = a.back(); a.pop_back();
		int y = a.back(); a.pop_back();
		ans.push_back({x, u, y});
	}
	if ( a.size() == 1 ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) if ( !vis[i] ) DFS(i, 0);
	printf("%d\n", ans.size());
	for ( auto it : ans ) printf("%d %d %d\n", it.u, it.v, it.w);
    return 0;
}

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

const int maxn = 1010;

int n1, n2, m, match[maxn], ans; bool vis[maxn];
vector<int> Edge[maxn];

inline void add(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); }

inline bool DFS(int u)
{
	if ( vis[u] ) return false; vis[u] = true;
	for ( auto v : Edge[u] ) if ( !match[v] || DFS(match[v]) )
	{
		match[u] = v; match[v] = u;
		return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n1, &n2, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v + n1); }
	REP(i, 1, n1) { mem(vis); if ( DFS(i) ) ++ ans; }
	printf("%d\n", ans); 
	REP(i, 1, n1) printf("%d ", max(0, match[i] - n1)); puts("");
    return 0;
}

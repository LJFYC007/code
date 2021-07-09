/***************************************************************
	File name: pigeons.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 10时32分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, ans, col[maxn], tot, Root, size[maxn], S, a[maxn];
vector<int> Edge[maxn]; 

inline void add(int u, int v) { Edge[u].push_back(v); }
inline void erase(int x, int y)
{
	for ( int i = 0; i < Edge[x].size(); ++ i ) if ( Edge[x][i] == y ) 
		swap(Edge[x][i], Edge[x][Edge[x].size() - 1]);
	if ( !Edge[x].empty() && Edge[x].back() == y ) Edge[x].pop_back();
}

inline int Get(int u, int fa)
{
	int ret = 1;
	for ( auto v : Edge[u] ) if ( v != fa ) ret += Get(v, u);
	return ret;
}

inline void GetRoot(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( auto v : Edge[u] ) if ( v != fa && !col[v] ) 
	{
		GetRoot(v, u); size[u] += size[v];
		Max = max(Max, size[v]);
	}
	if ( max(Max, S - size[u] - 1) <= S / 2 ) Root = u;
}

inline void DFS1(int u, int fa, int dep, int val)
{
	a[dep] += val; size[u] = 1;
	for ( auto v : Edge[u] ) if ( v != fa && !col[v] )
	{
		DFS1(v, u, dep ^ 1, val);
		size[u] += size[v];
	}
}

inline void DFS(int u)
{
	DFS1(u, 0, 0, 1);
	REP(i, 0, size[u]) ans += a[i] * a[i];
	DFS1(u, 0, 0, -1);
	for ( auto v : Edge[u] ) if ( !col[v] ) 
	{
		DFS1(v, u, 0, 1);
		REP(i, 0, size[v]) ans -= a[i] * a[i];
		DFS1(v, u, 0, -1);
	}
	col[u] = tot;
	for ( auto v : Edge[u] ) if ( !col[v] ) { S = size[v]; GetRoot(v, 0); DFS(Root); }
}

inline void Solve()
{
	tot = ans = 0; mem(col);
	REP(i, 1, n) if ( !col[i] ) { ++ tot; S = Get(i, 0); GetRoot(i, 0); DFS(Root); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("pigeons.in", "r", stdin);
    freopen("pigeons.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m); Solve();
	while ( m -- ) 
	{
		int op, x, y; scanf("%d%d%d", &op, &x, &y);
		if ( op == 1 && col[x] != col[y] ) { add(x, y); add(y, x); } 
		if ( op == 2 ) { erase(x, y); erase(y, x); }
		Solve(); printf("%d\n", ans);
	}
    return 0;
}

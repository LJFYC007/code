/***************************************************************
	File name: AGC025E.cpp
	Author: ljfcnyali
	Create time: 2021年05月02日 星期日 19时31分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4010;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, ans, c[maxn], dis[maxn], anc[maxn], dfn[maxn];
multiset<pii> Set[maxn]; bool use[maxn][maxn];
pii a[maxn];
bool vis1[maxn], vis2[maxn];

inline bool calc(int u, int v) { if ( use[u][v] || use[v][u] ) return use[u][v]; return dfn[u] < dfn[v]; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void Solve(int x, int op)
{
	if ( x <= m ) { if ( op ) swap(a[x].first, a[x].second); return ; }
	Solve(a[x].first, op); Solve(a[x].second, op ^ 1);
}

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		anc[v] = u; dis[v] = dis[u] + 1; DFS(v, u);
	}
	if ( Set[u].size() == 0 ) return ; 
	auto it = Set[u].begin();
	while ( it != Set[u].end() ) 
	{
		if ( (*it).first != u ) { ++ it; continue ; }
		Solve((*it).second, 0); it = Set[u].erase(it);
	}
	if ( Set[u].size() == 0 ) return ; 
	if ( Set[u].size() == 1 ) 
	{
		auto it = Set[u].begin(); int v = (*it).first, id = (*it).second;
		Set[u].erase(it); Set[v].erase(pii(u, id)); Set[v].insert(pii(fa, id)); if ( v != fa ) Set[fa].insert(pii(v, id));
		return ; 
	}
	auto itl = Set[u].begin(), itr = -- Set[u].end();
	Set[(*itl).first].erase(pii(u, (*itl).second)); Set[(*itr).first].erase(pii(u, (*itr).second));
	if ( calc((*itl).first, (*itr).first) ) swap(itl, itr);
	if ( use[(*itl).first][u] ) swap(a[(*itl).second].first, a[(*itl).second].second);
	if ( use[(*itr).first][u] ) swap(a[(*itr).second].first, a[(*itr).second].second);
	a[++ k] = pii((*itl).second, (*itr).second);

	Set[(*itl).first].insert(pii((*itr).first, k)); if ( (*itl).first != (*itr).first ) Set[(*itr).first].insert(pii((*itl).first, k));
	Set[u].erase(itl); Set[u].erase(itr);
	while ( !Set[u].empty() ) 
	{
		auto it = Set[u].begin(); int v = (*it).first, id = (*it).second;
		Set[u].erase(it); Set[v].erase(pii(u, id)); Set[v].insert(pii(fa, id)); if ( v != fa ) Set[fa].insert(pii(v, id));
	}
}

inline void Move(int x) { if ( c[x] < 2 ) { ++ c[x]; ++ ans; } }

inline void Get(int x, int y)
{
	int a = x, b = y;
	if ( dis[x] < dis[y] ) swap(x, y);
	while ( dis[x] > dis[y] ) { Move(x); x = anc[x]; } 
	while ( x != y ) { Move(x); Move(y); x = anc[x]; y = anc[y]; } 

	int t = x;
	while ( a != t ) { vis1[a] = true; a = anc[a]; } 
	while ( b != t ) { vis2[b] = true; b = anc[b]; } 
}

inline void DFS1(int u, int fa)
{
	dfn[u] = ++ k; 
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) 
	{
		use[u][To[i]] = true; DFS1(To[i], u);
		REP(j, 1, n) use[u][j] |= use[To[i]][j];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v ;scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	DFS1(1, 0);
	REP(i, 1, m) 
	{ 
		int u, v; scanf("%d%d", &u, &v); Set[u].insert(pii(v, i)); Set[v].insert(pii(u, i)); 
		if ( calc(u, v) ) swap(u, v); a[i] = pii(u, v); 
	}
	k = m; dis[1] = 1; DFS(1, 0);
	REP(i, 1, m) Get(a[i].first, a[i].second);

	REP(i, 1, n) 
	{
		if ( c[i] == 2 && (!vis1[i] || !vis2[i]) ) cerr << i << endl;
		// if ( c[i] == 1 && !vis1[i] && !vis2[i] ) cerr << i << endl;
	}

	printf("%d\n", ans); REP(i, 1, m) printf("%d %d\n", a[i].first, a[i].second);
    return 0;
}

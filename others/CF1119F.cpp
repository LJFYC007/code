/***************************************************************
	File name: CF1119F.cpp
	Author: ljfcnyali
	Create time: 2021年05月25日 星期二 09时05分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 2.5e5 + 10;

int n, k, f[maxn][2], s[maxn], deg[maxn], ans, dfn[maxn], tot, anc[maxn], W[maxn];
set<pii> Edge[maxn], p; bool vis[maxn]; vector<int> a[maxn];
multiset<int, greater<int> > A[maxn]; multiset<int> B[maxn]; 

inline void add(int u, int v, int w) { Edge[u].insert(pii(v, w)); ++ deg[u]; }

inline void Insert(int u, int val)
{
	A[u].insert(val); s[u] += val;
	auto it = A[u].begin(); val = *it; A[u].erase(it); s[u] -= val;
	B[u].insert(val);
}

inline void Erase(int u, int val)
{
	if ( A[u].find(val) != A[u].end() ) { A[u].erase(A[u].find(val)); s[u] -= val; } 
	else B[u].erase(B[u].find(val));
}

inline int Get(int u, int k)
{
	if ( k == -1 ) return s[u];
	while ( B[u].size() > k )
	{
		auto it = B[u].begin(); int val = *it;
		A[u].insert(val); s[u] += val; B[u].erase(it);
	}
	while ( B[u].size() < k && !A[u].empty() ) 
	{
		auto it = A[u].begin(); int val = *it;
		A[u].erase(it); s[u] -= val; B[u].insert(val);
	}
	return s[u];
}

inline void DFS(int u, int fa)
{
	vis[u] = true; int sum = 0;
	for ( auto it : Edge[u] ) 
	{
		int v = it.x, w = it.y; if ( v == fa ) continue ; 
		DFS(v, u); 
		if ( f[v][0] + w <= f[v][1] ) sum += f[v][0] + w; 
		else { sum += f[v][1]; Insert(u, f[v][0] + w - f[v][1]); }
	}
	f[u][0] = sum + Get(u, k);
	f[u][1] = sum + Get(u, k - 1);
	for ( auto it : Edge[u] ) 
	{
		int v = it.x, w = it.y; if ( v == fa ) continue ; 
		if ( f[v][0] + w > f[v][1] ) Erase(u, f[v][0] + w - f[v][1]);
	}
}

inline void DFS1(int u, int fa)
{
	dfn[u] = ++ tot; p.insert(pii(tot, u));
	for ( auto it : Edge[u] ) 
	{
		int v = it.x; if ( v == fa ) continue ;
		anc[v] = u; W[v] = it.y; DFS1(v, u);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); } 
	DFS1(1, 0); REP(i, 2, n) a[deg[i]].push_back(i);
	REP(o, 0, n - 1)
	{
		k = o; ans = 0;
		for ( auto it : p ) if ( !vis[it.y] ) 
		{ 
			DFS(it.y, 0); 
			ans += min(f[it.y][0] + W[it.y], f[it.y][1]); 
		}
		for ( auto it : p ) vis[it.y] = false;
		for ( auto it : a[o] ) 
		{
			p.erase(pii(dfn[it], it));
			for ( auto i : Edge[it] ) Edge[i.x].erase(pii(it, i.y));
			Edge[it].clear();
			if ( deg[anc[it]] > o ) Insert(anc[it], W[it]);
		}
		printf("%lld ", ans);
	}
	puts("");
    return 0;
}

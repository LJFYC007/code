/***************************************************************
	File name: CF521E.cpp
	Author: ljfcnyali
	Create time: 2021年05月26日 星期三 15时24分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], anc[maxn], a[maxn];
bool vis[maxn]; vector<pii> b;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	while ( dis[x] > dis[y] ) x = anc[x];
	if ( x == y ) return x;
	while ( anc[x] != anc[y] ) { x = anc[x]; y = anc[y]; }
	return anc[x];
}

inline void DFS1(int u, int fa)
{
	vis[u] = true; 
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( !vis[v] ) { anc[v] = u; dis[v] = dis[u] + 1; DFS1(v, u); }
		else if ( dis[u] > dis[v] ) { ++ a[u]; -- a[v]; }
	}
}

inline void DFS3(int u, int fa, int x)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( anc[v] == u ) DFS3(v, u, x);
		else if ( dis[u] > dis[v] && dis[v] <= x ) b.push_back(pii(u, v));
	}
}

inline void out(int x, int y, int z, int w)
{
	vector<int> p; int u = x; while ( u != y ) { p.push_back(u); u = anc[u]; } 
	p.push_back(y); u = z; while ( z != w ) { p.push_back(z); z = anc[z]; } p.push_back(w);
	printf("%zu ", p.size()); for ( auto it : p ) printf("%d ", it); puts("");
}

inline void DFS2(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( anc[v] != u ) continue ; 
		DFS2(v, u); a[u] += a[v];
	}
}

inline void DFS4(int u, int fa)
{
	if ( a[u] >= 2 ) 
	{
		puts("YES"); DFS3(u, fa, dis[fa]);
		sort(b.begin(), b.end(), [](const pii &a, const pii &b) { return dis[a.second] > dis[b.second]; });
		int x = LCA(b[0].first, b[1].first);
		vector<int> p; int t = x; while ( t != fa ) { p.push_back(t); t = anc[t]; }
		p.push_back(fa); reverse(p.begin(), p.end());
		printf("%zu ", p.size()); for ( auto it : p ) printf("%d ", it); puts("");
		out(fa, b[0].second, b[0].first, x);
		out(fa, b[1].second, b[1].first, x);
		exit(0);
	}
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( anc[v] != u ) continue ; 
		DFS4(v, u); 
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) if ( !vis[i] ) { dis[i] = 1; DFS1(i, 0); DFS2(i, 0); DFS4(i, 0); }
	puts("NO");
    return 0;
}

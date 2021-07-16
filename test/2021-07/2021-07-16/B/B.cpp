/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月16日 星期五 11时32分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, dis[maxn], deg[maxn];
bool vis[maxn], use[maxn]; 
struct node { int x, y, v; } ;
bool operator < (node a, node b)
{
	return a.x < b.x || (a.x == b.x && (a.y < b.y || (a.y == b.y && a.v < b.v)));
}
multiset<node> Edge[maxn];
vector<int> a;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int id)
{
	vector<pii> p; vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( !vis[v] ) { dis[v] = dis[u] + 1; DFS(v, u, i / 2); }
		if ( !use[i / 2] && dis[v] > dis[u] ) 
			p.push_back(pii(i / 2, v));
	}
	if ( p.size() % 2 == 1 ) p.push_back(pii(id, fa));
	for ( int i = 0; i < p.size(); i += 2 ) 
	{
		Edge[p[i].second].insert({p[i].first, p[i + 1].first, p[i + 1].second});
		Edge[p[i + 1].second].insert({p[i + 1].first, p[i].first, p[i].second});
		++ deg[p[i].second]; ++ deg[p[i + 1].second];
		use[p[i].first] = use[p[i + 1].first] = true;	
	}
}

inline void Solve(int u, int s)
{
	if ( u != s && deg[u] % 2 == 0 ) 
	{
		printf("%d %d %zu\n", s, u, a.size());
		for ( auto it : a ) printf("%d ", it);
		puts(""); return ;
	}
	assert(!Edge[u].empty());
	auto it = Edge[u].begin();	
	// cerr << u << " " << s << endl;
	int x = it -> x, y = it -> y, v = it -> v;
	// cerr << x << " " << y << " " << v << endl;
	deg[u] ^= 1; deg[v] ^= 1;	
	a.push_back(x); a.push_back(y);
	Edge[u].erase(Edge[u].find({x, y, v}));
	Edge[v].erase(Edge[v].find({y, x, u}));
	Solve(v, s);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS(1, 0, 0);
	REP(i, 1, n) if ( deg[i] & 1 ) 
	{
		a.clear();
		Solve(i, i);
	}
    return 0;
}

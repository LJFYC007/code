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
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, k, ans, f[maxn], size[maxn];
map<int, set<int> > Edge[maxn];
queue<int> Q;
bool vis[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline int calc(int n) { return n * (n - 1) / 2; }

inline void Merge(int x, int y)
{
	x = find(x); y = find(y);
	if ( x == y ) return ;
	if ( size[x] > size[y] ) swap(x, y);
	f[x] = y; size[y] += size[x];
	for ( auto i : Edge[x] ) 
	{
		auto it = i.second;	
		for ( auto j : it ) Edge[y][i.first].insert(j);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); Edge[v][w].insert(u); }
	REP(i, 1, n) { f[i] = i; size[i] = 1; Q.push(i); vis[i] = true; }
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		if ( find(u) != u ) continue ;
		for ( auto i : Edge[u] ) 
		{
			auto it = i.second; int x = find(*it.begin()), lst = size[x];
			Edge[u][i.first].clear(); 
			for ( auto j : it ) if ( j != x ) Merge(x, j);
			x = find(x); if ( !vis[x] && size[x] != lst ) { vis[x] = true; Q.push(x); }
			Edge[u][i.first].insert(x);
		}
		vis[u] = false;
	}
	REP(i, 1, n) if ( find(i) == i ) ans += calc(size[i]);
	printf("%lld\n", ans);
    return 0;
}

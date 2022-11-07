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

const int maxn = 1e5 + 10;

int n, d, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans[maxn];
vector<pii> prime[maxn];
vector<int> f[maxn]; bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int calc(int x, int y)
{
	if ( vis[x] || vis[y] ) return 0;
	int i = 0, j = 0, sum = 1;
	while ( i < prime[x].size() || j < prime[y].size() ) 
	{
		if ( i < prime[x].size() && j < prime[y].size() && prime[x][i].first == prime[y][j].first ) 
		{
			if ( prime[x][i].second + prime[y][j].second > d ) return 0; 
			if ( (prime[x][i].second + prime[y][j].second) % 2 == 1 ) 
				sum = -sum;
			++ i; ++ j;
		}
		else if ( (i < prime[x].size() && j < prime[y].size() && prime[x][i].first < prime[y][j].first) || j == prime[y].size() ) 
		{ 
			if ( prime[x][i].second % 2 == 1 ) sum = -sum;
			++ i;
		}
		else
		{ 
			if ( prime[y][j].second % 2 == 1 ) sum = -sum;
			++ j;
		}
	}
	return sum;
}

inline void DFS(int u, int fa)
{
	f[u].push_back(u); ans[u] += calc(a[u], a[u]);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u); ans[u] += ans[v];
		for ( auto it : f[v] ) for ( auto j : f[u] ) 
			ans[u] += calc(a[it], a[j]);
		for ( auto it : f[v] ) f[u].push_back(it);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &d);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n)
	{
		int x = i;
		for ( int j = 2; j * j <= x; ++ j ) if ( x % j == 0 ) 
		{
			int num = 0;
			while ( x % j == 0 ) { x /= j; ++ num; }
			if ( num > d ) vis[i] = true;
			prime[i].push_back(pii(j, num));
		}
		if ( x > 1 ) prime[i].push_back(pii(x, 1));
	}
	DFS(1, 0);
	REP(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}

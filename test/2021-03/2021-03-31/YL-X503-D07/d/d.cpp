#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1.6e6 + 10;
const int Mod = 998244353;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], a[maxn], anc[maxn][22], dis[maxn];
long long r[maxn];
map<int, int> Map;
pii Edge[maxn], Q[maxn];

inline void add(int u, int v) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
} 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; anc[v][0] = u;
		dis[v] = dis[u] + 1; a[v] = 1ll * a[v] * a[u] % Mod; DFS(v, u);
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 21; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 21; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; } 
	return anc[x][0];
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("d18.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	f[1] = 1; REP(i, 2, maxn - 10) f[i] = (1ll * (i - 2) * f[i - 1] + 1) % Mod;
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &r[i]);
	REP(i, 1, n - 1) 
	{
		int x, y; scanf("%lld%lld", &x, &y);
		Edge[i] = pii(x, y); Map[x] = Map[y] = true;
	}
	scanf("%lld", &m);
	REP(i, 1, m) { int x, y; scanf("%lld%lld", &x, &y); Q[i] = pii(x, y); }
	for ( auto it : Map ) { Map[it.first] = ++ k; a[k] = 1; }
	REP(i, 1, n) a[k + i] = f[r[i] - r[i - 1]];
	for ( auto it : Map ) { int x = lower_bound(r + 1, r + n + 1, it.first) - r; add(it.second, k + x); }	
	REP(i, 1, n - 1) add(Map[Edge[i].first], Map[Edge[i].second]);

	a[0] = dis[1] = 1; DFS(1, 0); 
	REP(j, 1, 21) REP(i, 1, k + n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(i, 1, m)
	{
		int x = Map[Q[i].first], y = Map[Q[i].second];
		if ( !x ) x = k + lower_bound(r + 1, r + n + 1, Q[i].first) - r;
		if ( !y ) y = k + lower_bound(r + 1, r + n + 1, Q[i].second) - r;
		int t = LCA(x, y), ans = 1ll * a[x] * a[y] % Mod * power(a[t], Mod - 2) % Mod * power(a[anc[t][0]], Mod - 2) % Mod;
		if ( Q[i].first == Q[i].second ) ans = 1;
		printf("%lld\n", (ans + Mod) % Mod);
	}
	return 0;
}

/***************************************************************
	File name: T185754.cpp
	Author: ljfcnyali
	Create time: 2021年07月14日 星期三 15时35分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int n, f[maxn][2][3], Begin[maxn], Next[maxn], To[maxn], e, a[maxn], g[2], h[2], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u);
	}

	// 0 OR -> 1 或者 1 AND -> 0
	mem(g); g[0] = 1; 
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		h[0] = g[0] * (a[v] != a[u] ? f[v][a[v]][1] : f[v][a[u] ^ 1][1]);
		h[1] = g[1] * (f[v][0][1] + f[v][1][1]) + g[0] * ((a[v] == a[u] ? f[v][a[u]][1] : 0) + (a[v] == a[u] ? f[v][a[u] ^ 1][0] : 0));
		REP(j, 0, 1) { g[j] = h[j] % Mod; h[j] = 0; } 
	}
	f[u][a[u] ^ 1][0] += g[1]; // f[u][a[u] ^ 1][1] += g[1];
	if ( a[fa] != a[u] ) f[u][a[u] ^ 1][1] += g[0];
	else { f[u][a[u] ^ 1][2] += g[0]; f[u][a[u] ^ 1][1] += g[0]; }
	if ( u == 1 ) ans += g[1];

	// 1 OR -> 1 或者 0 AND -> 0
	int ret = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		ret = ret * (f[v][0][0] + f[v][1][0] + f[v][0][2] + f[v][1][2]) % Mod;
	}
	f[u][a[u]][0] += ret; f[u][a[u]][1] += ret;
	if ( u == 1 ) ans += ret;

	// 1 AND -> 1 或者 0 OR -> 0
	ret = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		ret = ret * (a[v] == a[u] ? f[v][a[v]][0] + f[v][a[v]][2] : 0) % Mod;
	}
	if ( a[fa] == a[u] ) f[u][a[u]][0] += ret;
	if ( u == 1 ) ans += ret;

	REP(i, 0, 1) REP(j, 0, 1) f[u][i][j] %= Mod;
	// if ( u == 2 ) { REP(i, 0, 1) REP(j, 0, 1) cout << i << " " << j << " " << f[u][i][j] << endl; } 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 	
	DFS(1, 0);
	printf("%lld\n", ans % Mod);
    return 0;
}

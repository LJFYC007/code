/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 10时18分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6010;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn << 1], To[maxn << 1], e, Root, fac[maxn], inv[maxn];
int size[maxn], Hash[maxn], prime[maxn], tot, f[maxn][maxn], g[maxn], h[maxn], t[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 
inline void add(int u, int v) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
} 

inline void DFS1(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u); size[u] += size[v];
		Max = max(Max, size[v]);
	}
	if ( max(Max, n + n - 1 - size[u]) * 2 <= n + n - 1 ) Root = u;
}

inline void DFS2(int u, int fa)
{
	size[u] = 1; Hash[u] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS2(v, u); size[u] += size[v];
		Hash[u] = (Hash[u] + Hash[v] * prime[size[v]]) % Mod;
	}
}

inline void DFS(int u, int fa)
{
	map<int, pii> Map;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( !Map.count(Hash[v]) ) { Map[Hash[v]] = pii(v, 1); DFS(v, u); } 
		else ++ Map[Hash[v]].second;
	}
	
	f[u][0] = 1; if ( u <= n ) f[u][1] = 1;
	for ( auto it : Map ) 
	{
		mem(g); g[0] = t[0] = 1; int v = it.second.first;
		REP(o, 1, it.second.second)
		{
			REP(j, 0, n) REP(k, 1, j)
				h[j] = (h[j] + g[j - k] * f[v][k] % Mod * C(j - 1, k - 1)) % Mod;
			if ( u == 1 ) 
			{
				REP(j, 0, n) cout << h[j] * inv[j] % Mod << " "; cout << endl;
			}
			REP(j, 0, n) { t[j] = (t[j] + h[j]) % Mod; g[j] = h[j]; h[j] = 0; }
		}

		REP(j, 0, n) REP(k, 0, j)
			h[j] = (h[j] + f[u][j - k] * t[k] % Mod * C(j, k)) % Mod;
		REP(j, 0, n) { f[u][j] = h[j]; h[j] = t[j] = 0; }
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, n + i); add(v, n + i); } 
	REP(i, 2, 10000)
	{
		bool flag = true;
		for ( int j = 2; j * j <= i; ++ j ) if ( i % j == 0 ) { flag = false; break ; } 
		prime[++ tot] = i;
	}
	DFS1(1, 0); DFS2(Root, 0); DFS(Root, 0);
	REP(k, 1, n) printf("%lld ", (f[Root][k] + Mod) % Mod); puts("");
    return 0;
}

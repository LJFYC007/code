/***************************************************************
	File name: ARC101E.cpp
	Author: ljfcnyali
	Create time: 2021年06月15日 星期二 09时48分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

#define size __ljf_has_no_family__
int n, f[maxn][maxn], g[maxn], h[maxn], fac[maxn], inv[maxn], ans, size[maxn];
vector<int> Edge[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return fac[n] * inv[m] % Mod * inv[n - m] % Mod; }

inline void DFS(int u, int fa)
{
	f[u][1] = 1; size[u] = 1;
	for ( auto v : Edge[u] ) 
	{
		if ( v == fa ) continue ; 
		DFS(v, u);
		REP(i, 1, size[u]) REP(j, 1, size[v])
		{
			h[i + j] = (h[i + j] + f[u][i] * f[v][j]) % Mod;
			h[i] = (h[i] - f[u][i] * f[v][j] % Mod * g[j]) % Mod;
		}
		size[u] += size[v];
		REP(i, 1, size[u]) { f[u][i] = h[i]; h[i] = 0; }
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
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); Edge[u].push_back(v); Edge[v].push_back(u); }
	for ( int i = 2; i <= n; i += 2 ) 
	{
		int j = i / 2;
		g[i] = C(i, j) * fac[j] % Mod * power((Mod + 1) / 2, j) % Mod;
	}
	DFS(1, 0);
	REP(i, 1, n) ans = (ans + f[1][i] * g[i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}


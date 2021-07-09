#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2020;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn], To[maxn], e, r[maxn], f[maxn][maxn], fac[maxn], size[maxn], g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	size[u] = 1; f[u][0] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; DFS(v);
		REP(j, 0, size[u]) REP(k, 1, size[v])
			g[j + k] = (g[j + k] + f[u][j] * f[v][k]) % Mod;
		size[u] += size[v];
		REP(j, 0, size[u]) { f[u][j] = g[j]; g[j] = 0; } 
	}
	++ f[u][1];
}

signed main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree1.out", "w", stdout);
	scanf("%lld", &n); REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); } 
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	REP(i, 1, n) scanf("%lld", &r[i]);
	DFS(1); int ans = 0;
 	REP(i, 1, n) ans = (ans + r[i] * f[1][i] % Mod * fac[i]) % Mod;
	REP(i, 1, n) { REP(j, 1, n) cout << f[i][j] << " "; cout << endl; }
	REP(i, 1, n) printf("%lld ", f[1][i]); puts("");
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

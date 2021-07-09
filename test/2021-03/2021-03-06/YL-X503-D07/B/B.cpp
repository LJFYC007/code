#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 310;
const int Mod = 1e9 + 7;

int n, x, b[maxn], c[maxn], d[maxn], p[maxn];
int a[maxn][maxn], ans = 1;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

namespace Subtask
{
const int maxn = 2e6 + 10;
int ans, f[maxn], g[maxn], Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
bool vis[maxn];
queue<int> Q;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline int sgn(int x) { return x & 1 ? -1 : 1; } 

int main()
{
	REP(i, 1, n) { scanf("%lld", &d[i]); f[i] = 1; } 
	REP(i, 2, n) { scanf("%lld%lld%lld", &p[i], &b[i], &c[i]); } 
	REP(i, 2, n) add(i, p[i]);
	REP(i, 1, n) if ( !deg[i] ) Q.push(i);

	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop(); if ( u == 1 ) continue ; 
		int v = p[u]; -- deg[v]; if ( !deg[v] ) Q.push(v); 
		g[v] = (g[v] * (f[u] * d[u] % Mod + g[u]) + f[v] * (-b[u]) % Mod * c[u] % Mod * f[u]) % Mod;
		f[v] = f[v] * (f[u] * d[u] % Mod + g[u]) % Mod;
	}
	int ans = (f[1] * d[1] + g[1]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &x);
	if ( x == 0 ) return Subtask :: main();
	REP(i, 1, n) REP(j, 1, n) a[i][j] = x;
	REP(i, 1, n) { scanf("%lld", &d[i]); a[i][i] = d[i]; } 
	REP(i, 2, n) scanf("%lld%lld%lld", &p[i], &b[i], &c[i]);
	REP(i, 2, n) { a[p[i]][i] = b[i]; a[i][p[i]] = c[i]; }

	REP(i, 1, n)
	{
		int pos = -1;
		REP(j, i, n) if ( a[j][i] != 0 ) { pos = j; break ; } 
		if ( pos == -1 ) { puts("0"); return 0; } 
		if ( pos != i ) { REP(j, 1, n) swap(a[i][j], a[pos][j]); ans = -ans; } 
		REP(j, i + 1, n)
		{
			int tmp = a[j][i] * power(a[i][i], Mod - 2) % Mod;
			REP(k, 1, n) a[j][k] = (a[j][k] - a[i][k] * tmp) % Mod;
		}
	}
	REP(i, 1, n) ans = ans * a[i][i] % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

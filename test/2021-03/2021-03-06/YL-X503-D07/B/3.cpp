#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, x, p[maxn], b[maxn], c[maxn], d[maxn], ans, f[maxn][2][3], g[2][3];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &x);
	REP(i, 1, n) { scanf("%lld", &d[i]); f[i][0][0] = 1; }  
	REP(i, 2, n) { scanf("%lld%lld%lld", &p[i], &b[i], &c[i]); } 

	for ( int u = n; u >= 2; -- u ) 
	{
		int v = p[u]; 
		REP(j, 0, 2)
		{
			g[0][j] = f[v][0][j] * (f[u][1][j] + f[u][0][j] * d[u] % Mod) % Mod;
			g[1][j] = (f[v][1][j] * (f[u][0][j] * d[u] % Mod + f[u][1][j]) + f[v][0][j] * (-b[u]) % Mod * c[u] % Mod * f[u][0][j]) % Mod;
		}

		REP(o, 0, 1) g[o][1] = (g[o][1] + f[v][o][0] * (-x) % Mod * c[u] % Mod * f[u][0][0]) % Mod; // u 连出一条边，未定终点且不是v
		g[1][2] = (g[1][2] + f[v][0][0] * (f[u][0][1] * d[u] % Mod + f[u][1][1])) % Mod; // v 被定为del, u 子树内连出边
		g[1][2] = (g[1][2] + f[v][0][0] * (-x) % Mod * b[u] % Mod * f[u][0][0]) % Mod;	// u 被定为del，删去v
		REP(o, 0, 1) g[o][2] = (g[o][2] + f[v][o][0] * f[u][0][0] % Mod * x) % Mod; // u 被定为del，不删

		REP(o, 0, 1) REP(x, 0, 2) f[v][o][x] = g[o][x];
	}

	ans = ((f[1][0][0] + f[1][0][2]) * d[1] + f[1][1][0] + f[1][1][2]) % Mod;
	ans = (ans + f[1][0][0] * x) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

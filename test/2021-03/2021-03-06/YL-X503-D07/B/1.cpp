#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, x, p[maxn], b[maxn], c[maxn], d[maxn], ans, f[maxn][2][4], g[2][4];
int Begin[maxn], Next[maxn], To[maxn], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void DFS(int u)
{
	int sum = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; DFS(v);
		REP(j, 0, 1) // 正常转移
		{
			g[0][j] = f[u][0][j] * (f[v][1][0] + f[v][0][0] * d[v] % Mod) % Mod; 
			g[1][j] = (f[u][1][j] * (f[v][1][0] + f[v][0][0] * d[v] % Mod) + f[u][0][j] * (-b[v]) % Mod * c[v] % Mod * f[v][0][0]) % Mod;
		}
		g[0][1] = (g[0][1] + f[u][0][0] * (f[v][1][1] + f[v][0][1] * d[v] % Mod)) % Mod; 
		g[1][1] = (g[1][1] + f[u][1][0] * (f[v][1][1] + f[v][0][1] * d[v] % Mod) + f[u][0][0] * (-b[v]) % Mod * c[v] % Mod * f[v][0][1]) % Mod;

		// 维护2, 3
		REP(j, 2, 3) g[1][j] = f[u][1][j] * (f[v][1][0] + f[v][0][0] * d[v] % Mod) % Mod;
		g[1][2] = (g[1][2] + f[u][0][0] * f[v][1][2] % Mod * (-b[v])) % Mod;
		g[1][3] = (g[1][3] + f[u][0][0] * f[v][1][3] % Mod * (-c[v])) % Mod;

		// 维护贡献
		g[1][1] = (g[1][1] + f[u][1][2] * f[v][1][3] % Mod * x % Mod * (-c[v])) % Mod;	
		g[1][1] = (g[1][1] + (f[u][1][3] - 0) * f[v][1][2] % Mod * x % Mod * (-b[v])) % Mod;	

		// 以当前点为del点
		sum = sum * (f[v][0][0] * d[v] % Mod + f[v][1][0]) % Mod;
		
		REP(x, 0, 1) REP(y, 0, 3) f[u][x][y] = g[x][y];
	}
	f[u][1][1] = (f[u][1][1] + sum * x) % Mod;
	// REP(x, 0, 1) REP(y, 0, 3) cout << f[u][x][y] << " "; cout << endl;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &x);
	REP(i, 1, n) { scanf("%lld", &d[i]); d[i] -= x; f[i][0][0] = 1; f[i][1][2] = f[i][1][3] = 1; }  
	REP(i, 2, n) { scanf("%lld%lld%lld", &p[i], &b[i], &c[i]); add(p[i], i); b[i] -= x; c[i] -= x; } 
	DFS(1);
	REP(o, 0, 1) ans = (ans + f[1][0][o] * d[1] + f[1][1][o]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

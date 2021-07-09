/***************************************************************
	File name: CF1517F.cpp
	Author: ljfcnyali
	Create time: 2021年04月27日 星期二 10时19分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn], To[maxn], e, ans[maxn], ret, f[maxn][maxn][2], g[maxn][2], Max[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int u, int fa, int x)
{
	f[u][0][0] = f[u][x][1] = 1; Max[u] = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u, x); 
		REP(k, 0, Max[u]) REP(j, 0, Max[v])
		{
			g[max(k, j + 1)][0] = (g[max(k, j + 1)][0] + f[u][k][0] * f[v][j][0]) % Mod;
			if ( j < x - k ) g[x - k][1] = (g[x - k][1] + f[u][x - k][1] * f[v][j][0]) % Mod;
			else g[j + 1][0] = (g[j + 1][0] + f[u][x - k][1] * f[v][j][0]) % Mod;
		}

		REP(k, 0, Max[u]) REP(j, x - Max[v], x)
		{
			if ( k <= j - 1 ) g[j - 1][1] = (g[j - 1][1] + f[u][k][0] * f[v][j][1]) % Mod;
			else g[k][0] = (g[k][0] + f[u][k][0] * f[v][j][1]) % Mod;
			g[max(x - k, j - 1)][1] = (g[max(x - k, j - 1)][1] + f[u][x - k][1] * f[v][j][1]) % Mod;
		}
		REP(k, 0, x) REP(o, 0, 1) { f[u][k][o] = g[k][o]; g[k][o] = 0; } 
		Max[u] = max(Max[u], Max[v] + 1);
	}
}

inline int Solve(int x)
{
	mem(f); DFS(1, 0, x);
	int sum = 0; REP(i, 0, x) sum = (sum + f[1][i][1]) % Mod; return sum;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	REP(i, 0, n) ans[i] = Solve(i);		
	REP(i, 1, n) ret = (ret + (ans[i] - ans[i - 1]) * (i - 1)) % Mod;
	ret = (ret + n - 1) * power((Mod + 1) / 2, n) % Mod;
	printf("%lld\n", (ret + Mod) % Mod);
    return 0;
}

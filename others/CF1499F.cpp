/***************************************************************
	File name: CF1499F.cpp
	Author: ljfcnyali
	Create time: 2021年03月19日 星期五 08时54分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, k, f[maxn][maxn], Begin[maxn], Next[maxn << 1], To[maxn << 1], e, suf[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	int sum = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS(v, u); sum = 1ll * sum * f[v][k] % Mod;
	}
	f[u][0] = sum; vector<int> p;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) p.push_back(To[i]);
	reverse(p.begin(), p.end());
	REP(len, 1, k)
	{
		int s1 = 1, x = min(len - 2, k - len - 1), y = min(len - 1, k - len - 1);
		if ( x < 0 ) x = k + 1; if ( y < 0 ) y = k + 1;
		int now = 0; suf[0] = 1;
		for ( auto v : p ) { ++ now; suf[now] = 1ll * suf[now - 1] * (f[v][y] + f[v][k]) % Mod; }
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( v == fa ) continue ; -- now;
			f[u][len] = (1ll * (f[v][len - 1] - (len >= 2 ? f[v][len - 2] : 0)) * s1 % Mod * suf[now] + f[u][len]) % Mod;
			s1 = 1ll * s1 * (f[v][x] + f[v][k]) % Mod;
		}
		f[u][len] = (f[u][len] + f[u][len - 1]) % Mod;
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	DFS(1, 0); printf("%d\n", (f[1][k] + Mod) % Mod);
    return 0;
}

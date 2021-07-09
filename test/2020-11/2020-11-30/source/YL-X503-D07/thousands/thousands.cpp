/***************************************************************
	File name: thousands.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 09时30分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 10010;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn], To[maxn], e, inv[maxn], f[maxn][maxn], g[maxn], size[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u][1] = 1; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); 
        REP(j, 0, size[u]) { g[j] = f[u][j]; f[u][j] = 0; }
        REP(j, 0, size[u]) REP(k, 0, size[v]) f[u][j + k] = (f[u][j + k] + g[j] * f[v][k]) % Mod;
        size[u] += size[v];
    }
    int ret = 1;
    REP(i, 1, size[u]) ret = (ret - f[u][i] * inv[i]) % Mod;
    f[u][0] = ret;
    ans = (ans + ret) % Mod;
}

signed main()
{
    freopen("thousands.in", "r", stdin);
    freopen("thousands.out", "w", stdout);
    scanf("%lld", &n); 
    REP(i, 1, n) inv[i] = power((Mod + 1) / 2, i * i);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    ans = ans * power(2, n * n) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

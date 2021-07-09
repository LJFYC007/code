/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2020年05月31日 星期日 20时30分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int f[maxn], g[maxn], n, Begin[maxn], Next[maxn], To[maxn], e;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    g[u] = f[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        int x = f[u], y = g[u];

        // link
        g[u] = y * g[v] % Mod;
        f[u] = (x * g[v] + y * f[v]) % Mod;

        // no link
        g[u] = (g[u] + y * f[v]) % Mod;
        f[u] = (f[u] + x * f[v]) % Mod;
    }
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    printf("%lld\n", f[1] * power(inv2, n - 1) % Mod);
    return 0;
}

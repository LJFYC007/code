/***************************************************************
	File name: centroid.cpp
	Author: ljfcnyali
	Create time: 2020年10月06日 星期二 22时18分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, k, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, f[maxn][510], g[maxn][510];
int h[maxn], anc[maxn], ans, H[maxn][510], size[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    f[u][0] = f[u][1] = size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v] = u; DFS1(v, u); 
        REP(j, 1, min(size[u], k)) REP(t, 0, min(size[v], (k - 1) / 2)) 
        {
            if ( j + t > k ) break ;
            h[j + t] = (h[j + t] + f[u][j] * f[v][t]) % Mod;
        }
        REP(j, 1, k) { f[u][j] = h[j]; h[j] = 0; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int fa)
{
    g[u][0] = H[u][0] = 1;
    REP(j, 0, k / 2) H[u][j + 1] = g[u][j];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        REP(j, 1, min(size[u], k / 2)) REP(t, 0, min(size[v], (k - 1) / 2)) 
        {
            if ( j + t > k / 2 ) break ;
            h[j + t] = (h[j + t] + H[u][j] * f[v][t]) % Mod;
        }
        REP(j, 1, k) { H[u][j] = h[j]; h[j] = 0; }
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        REP(j, 0, k) g[v][j] = H[u][j];
        REP(j, 1, min(size[u], k / 2)) REP(t, 1, min(size[v], (k - 1) / 2))
        {
            if ( j + t > k / 2 ) break ; 
            g[v][j + t] = (g[v][j + t] - g[v][j] * f[v][t]) % Mod;
        }
        DFS2(v, u);
    }
}

signed main()
{
    freopen("centroid.in", "r", stdin);
    freopen("centroid.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1, 0);
    REP(i, 1, n) REP(j, 0, k / 2)
    {
        int ret = f[i][k - j] * g[i][j] % Mod;
        if ( k - j == j && anc[i] < i ) 
            ans = (ans + ret * a[anc[i]]) % Mod;
        else 
            ans = (ans + ret * a[i]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

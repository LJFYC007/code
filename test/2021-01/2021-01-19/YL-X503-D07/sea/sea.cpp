/***************************************************************
	File name: sea.cpp
	Author: ljfcnyali
	Create time: 2021年01月19日 星期二 09时18分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 410;
const int Mod = 998244353;

int n, Begin[maxn << 1], Next[maxn << 1], To[maxn << 1], e;
int f[maxn][maxn], g[maxn][maxn], F[maxn], h[maxn], size[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS(To[i], u);
    REP(o, 0, n)
    {
        REP(i, 0, n) h[i] = 0; h[0] = 1;
        size[u] = 1;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ; 
            REP(j, 0, size[u]) { F[j] = h[j]; h[j] = 0; }
            REP(j, 0, size[u])
            {
                REP(k, 0, size[v]) h[j + k + 1] = (h[j + k + 1] + F[j] * f[v][k]) % Mod;
                h[j] = (h[j] + F[j] * g[v][o + 1]) % Mod;
            }
            size[u] += size[v];
        }
        f[u][o] = h[o] * (o + 1) % Mod;
    }
    REP(o, 1, n)
    {
        REP(i, 0, n) h[i] = 0; h[0] = 1;
        size[u] = 1;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ; 
            REP(j, 0, size[u]) { F[j] = h[j]; h[j] = 0; }
            REP(j, 0, size[u]) 
            {
                REP(k, 0, size[v]) h[j + k + 1] = (h[j + k + 1] + F[j] * f[v][k]) % Mod;
                h[j] = (h[j] + F[j] * g[v][o + 1]) % Mod;
            }
            size[u] += size[v];
        }
        REP(i, 0, o - 1) g[u][o - i] = (g[u][o - i] + h[i] * (o + 1)) % Mod;
    }
}

signed main()
{
    freopen("sea.in", "r", stdin);
    freopen("sea.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
    DFS(1, 0);
    int ans = 0; REP(i, 0, n) ans = (ans + f[1][i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

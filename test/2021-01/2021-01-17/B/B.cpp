/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 09时48分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, s, val[maxn], Begin[maxn], Next[maxn], To[maxn], e, f[maxn][2][2], deg[maxn], g[maxn], h[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; } 

inline void DFS(int u, int fa)
{
    if ( deg[u] == 1 ) f[u][0][1] = f[u][1][1] = val[u];
    int x = power(deg[u], Mod - 2), y = power(deg[u] - 1, Mod - 2), sum = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); g[u] = (g[u] + h[v] * x + g[v] * y) % Mod;
        sum = (sum + f[v][1][1]) % Mod;
    }
    g[u] = g[u] * x % Mod; h[u] = x;

    if ( deg[u] == 2 ) for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        f[u][1][1] = (f[u][1][1] + val[u] * g[v]) % Mod;
    }

    REP(o, 0, 1)
    {
        int x = power(deg[u] - o, Mod - 2), y = power(deg[u] - o - 1, Mod - 2);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            f[u][0][o] = (f[u][0][o] + f[v][1][1] * x) % Mod;
            f[u][1][o] = (f[u][1][o] + f[v][1][0] * x) % Mod;
            f[u][1][o] = (f[u][1][o] + h[v] * x % Mod * x % Mod * f[v][0][1]) % Mod;
            /*
            for ( int j = Begin[u]; j; j = Next[j] ) 
            {
                int w = To[j]; if ( w == fa || w == v ) continue ; 
                f[u][1][o] = (f[u][1][o] + h[v] * x % Mod * x % Mod * f[w][1][1]) % Mod;
                f[u][1][o] = (f[u][1][o] + g[v] * x % Mod * y % Mod * f[w][1][1]) % Mod;
            }
            */
            f[u][1][o] = (f[u][1][o] + h[v] * x % Mod * x % Mod * (sum - f[v][1][1])) % Mod;
            f[u][1][o] = (f[u][1][o] + g[v] * x % Mod * y % Mod * (sum - f[v][1][1])) % Mod;
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &s);
    REP(i, 1, n) scanf("%lld", &val[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
    ++ deg[s]; DFS(s, 0); printf("%lld\n", (f[s][1][1] + Mod) % Mod);
    return 0;
}

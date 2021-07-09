/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月13日 星期六 11时46分36秒
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
const int Mod = 1e9 + 9;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, ans, fac[maxn], inv[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

namespace Subtask2
{
    int Root, MAX, size[maxn], f[401][201][201], g[maxn], dfn[maxn], tot, id[maxn];

    inline void DFS(int u, int fa)
    {
        size[u] = 1; int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS(v, u); size[u] += size[v];
            Max = max(Max, size[v]);
        }
        Max = max(Max, n - size[u]);
        if ( Max < MAX ) { MAX = Max; Root = u; }
    }

    inline void DFS1(int u, int fa)
    {
        g[u] = size[u] = 1; 1; dfn[u] = ++ tot; id[tot] = u; int sum = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS1(v, u); sum += size[v]; size[u] += size[v];
            g[u] = g[u] * g[v] % Mod;
            g[u] = g[u] * C(sum, size[v]) % Mod;
        }
    }

    inline int main()
    {
        MAX = n; DFS(1, 0);
        DFS1(Root, 0);
        f[2][0][0] = 1;
        REP(i, 2, n) REP(j, 0, n - m) REP(k, 0, n - m)
        {
            f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % Mod;
            int x = size[id[i]];
            if ( j + x <= n - m ) f[i + x][j + x][k] = (f[i + x][j + x][k] + (f[i][j][k] * C(j + x, x) % Mod) * g[id[i]]) % Mod;
            if ( k + x <= n - m ) f[i + x][j][k + x] = (f[i + x][j][k + x] + (f[i][j][k] * C(k + x, x) % Mod) * g[id[i]]) % Mod;
        }
        printf("%lld\n", (f[n + 1][n - m][n - m] * fac[n - 2 * (n - m)] % Mod + Mod) % Mod);
        return 0;
    }
}

namespace Subtask1
{
    int num, size[maxn], f[maxn];

    inline void DFS(int u, int t, int dis, int fa)
    {
        if ( u == t ) { num = dis - 1; return ; }
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS(v, t, dis + 1, u);
        }
    }

    inline void DFS1(int u, int fa)
    {
        size[u] = 1;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS1(v, u); size[u] += size[v];
        }
    }

    inline void DFS2(int u, int fa)
    {
        f[u] = 1;
        int sum = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS2(v, u);
            f[u] = f[u] * f[v] % Mod;
            f[u] = f[u] * C(sum + size[v], sum) % Mod;
            sum += size[v];
        }
    }

    inline int main()
    {
        int ret = 0;
        REP(i, 1, n) REP(j, 1, n) 
        {
            num = 0;
            DFS(i, j, 0, 0);
            if ( n - num != m * 2 ) continue ;
            DFS1(i, 0);
            if ( size[j] != m ) continue ;
            DFS1(j, 0);
            if ( size[i] != m ) continue ;

            DFS2(i, 0); ans = f[j];
            DFS2(j, 0); ans = ans * f[i] % Mod;
            ret = (ret + ans) % Mod;
        }
        printf("%lld\n", (ret + Mod) % Mod);
        return 0;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    n = maxn - 10; fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 0; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    if ( 2 * m <= n ) return Subtask1 :: main();
    return Subtask2 :: main();
    return 0;
}

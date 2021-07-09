/***************************************************************
	File name: LibreOJ_2340.cpp
	Author: ljfcnyali
	Create time: 2020年07月31日 星期五 19时35分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1 << 21;
const int Mod = 998244353;

int n, m, p, Begin[maxn], Next[maxn], To[maxn], e, w[maxn], deg[22], Inv[maxn];
bool vis[22], use[22];
vector<int> f;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;; }

inline void DFS(int u)
{
    if ( vis[u] ) return ; vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        if ( !use[To[i]] ) continue ;
        ++ deg[To[i]]; DFS(To[i]);
    }
}

inline vector<int> FWT(vector<int> f, int op)
{
    REP(Mid, 0, n - 1)
        for ( int i = 0; i < (1 << n); i += (1 << Mid + 1) )
            REP(j, 0, (1 << Mid) - 1)
                f[i + j + (1 << Mid)] = (f[i + j + (1 << Mid)] + op * f[i + j]) % Mod;
    return f;
}

inline int Solve(vector<int> a)
{
    vector<int> f[22], g[22]; REP(i, 0, n) { f[i].resize(1 << n); g[i].resize(1 << n); }
    REP(i, 0, (1 << n) - 1) if ( a[i] > 0 ) g[__builtin_popcount(i)][i] = a[i];
    f[0][0] = 1; f[0] = FWT(f[0], 1);
    REP(i, 0, n) g[i] = FWT(g[i], 1); 
    REP(j, 1, n)
    {
        REP(i, 0, (1 << n) - 1) REP(k, 0, j - 1) 
            f[j][i] = (f[j][i] + f[k][i] * g[j - k][i]) % Mod;
        f[j] = FWT(f[j], -1);
        REP(i, 0, (1 << n) - 1) f[j][i] = f[j][i] * Inv[i] % Mod;
        if ( j != n ) f[j] = FWT(f[j], 1);
    }
    return f[n][(1 << n) - 1];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &p);
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) scanf("%lld", &w[i]);
    f.resize(1 << n); 
    REP(i, 1, (1 << n) - 1)
    {
        mem(vis); mem(deg); mem(use); int sum = 0;
        bool flag = true;
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) { sum += w[j]; use[j] = true; }
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) { DFS(j); break ; }
        REP(j, 1, n) if ( ((i >> j - 1) & 1) && (!vis[j] || deg[j] % 2 != 0) ) flag = false;
        if ( flag == false ) f[i] = power(sum, p);
        Inv[i] = power(power(sum, p), Mod - 2);
    }

    printf("%lld\n", (Solve(f) + Mod) % Mod);
    return 0;
}

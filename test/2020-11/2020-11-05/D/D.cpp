/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年11月08日 星期日 19时56分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int Mod = 998244353;

int n, m, a[maxn], f[maxn][maxn], L[maxn], deg[maxn], g[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve(int n)
{
    int ans = 1;
    REP(i, 1, n)
    {
        REP(j, 1, n)
        {
            if ( j == i ) continue ;
            int tmp = f[j][i] * power(f[i][i], Mod - 2) % Mod;
            REP(k, 1, n) f[j][k] = (f[j][k] - f[i][k] * tmp) % Mod;
        }
        ans = ans * f[i][i] % Mod;
    }
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    int lst = 0; REP(i, 1, n) { L[i] = lst + 1; scanf("%lld", &a[i]); lst += a[i]; }
    REP(i, 1, m)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        deg[u] = (deg[u] + a[v]) % Mod; ++ g[u][v];
        deg[v] = (deg[v] + a[u]) % Mod; ++ g[v][u];
    }
    -- a[n];
    REP(i, 1, n) REP(j, 1, n)
    {
        if ( a[j] == 0 ) { f[i][j] = 1; continue ; }
        if ( i != j ) 
        {
            int x = power(deg[j], a[j] - 1) * a[j] % Mod;
            f[i][j] = -x * g[i][j] % Mod;
        }
        else
        {
            int x = (a[j] * -g[i][j] + deg[j]) % Mod;
            f[i][j] = x * power(deg[j], a[j] - 1) % Mod;
        }
    }
    int ans = Solve(n);
    if ( a[n] == 0 ) ans = ans * power(lst, Mod - 2) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

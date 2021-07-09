/***************************************************************
	File name: P6478.cpp
	Author: ljfcnyali
	Create time: 2020年04月25日 星期六 15时49分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e3 + 10;
const int maxm = 1e4 + 10;
const int Mod = 998244353;

int n, a[maxn], size1[maxn], size2[maxn], f[maxn], g[maxn];
int Begin[maxm], Next[maxm], To[maxm], e, dp[maxn][maxn], fac[maxn], inv[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    dp[u][0] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        int n1 = min(size1[v], size2[v]), n2 = min(size1[u], size2[u]);
        REP(j, 0, n2) f[j] = dp[u][j]; 
        REP(j, 1, n1) REP(k, 0, n2) dp[u][j + k] = (dp[u][j + k] + dp[v][j] * f[k]) % Mod;
        size1[u] += size1[v]; size2[u] += size2[v];
    }
    if ( a[u] == 0 ) 
        for ( int i = size2[u]; i >= 0; -- i ) dp[u][i + 1] = (dp[u][i + 1] + dp[u][i] * (size2[u] - i)) % Mod;
    else 
        for ( int i = size1[u]; i >= 0; -- i ) dp[u][i + 1] = (dp[u][i + 1] + dp[u][i] * (size1[u] - i)) % Mod;
    if ( a[u] == 1 ) ++ size2[u];
    else ++ size1[u];
}

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%s", s + 1);
    REP(i, 1, n) a[i] = s[i] - '0';
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(i, 0, n / 2) f[i] = dp[1][i] * fac[n / 2 - i] % Mod;
//    REP(i, 0, n / 2 + 1) printf("%lld ", f[i]); puts("");
    REP(i, 0, n / 2)
    {
        int sum = 0;
        REP(j, i, n / 2 + 1) sum = (sum + ((j - i) & 1 ? -1 : 1) * C(j, i) * f[j]) % Mod;
        printf("%lld\n", (sum + Mod) % Mod);
    }
    return 0;
}

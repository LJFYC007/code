/***************************************************************
	File name: ball.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 09时41分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e3 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], f[maxn][maxn];
int h[maxn], fac[maxn], inv[maxn], size[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b) { int r = 1 ; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int u)
{
    int son = 0; f[u][0] = 1; size[u] = a[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        REP(j, 0, size[u]) { h[j] = f[u][j]; f[u][j] = 0; }
        REP(k, 0, size[v]) REP(j, 0, size[u])
            f[u][j + k] = (f[u][j + k] + h[j] * (f[v][k] * inv[k] % Mod * inv[size[v] - k] % Mod)) % Mod; 
        ++ son; size[u] += size[v];
    }
    int x = f[u][0];
    REP(j, 0, size[u] - 1) f[u][j] = f[u][j + 1] * fac[j + 1] % Mod * fac[size[u] - j - 1] % Mod;
    f[u][0] += x;
    if ( !son ) { REP(i, 0, size[u]) f[u][i] = 0; f[u][a[u] - 1] = 1; }
}

signed main()
{
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    scanf("%lld", &n);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); }
    REP(i, 1, n) scanf("%lld", &a[i]);
    DFS(1);
    printf("%lld\n", (f[1][0] + Mod) % Mod);
    return 0;
}

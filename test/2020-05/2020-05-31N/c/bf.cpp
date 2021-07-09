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

const int maxn = 2e3 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int f[maxn][maxn], g[maxn][maxn], n, Begin[maxn], Next[maxn], To[maxn], e;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1
{
    const int maxm = 2e6 + 10;
    int f[maxn]; 

    inline int main()
    {
        f[1] = 1; f[2] = 2;
        REP(i, 3, n * 2) f[i] = (f[i - 1] + f[i - 2]) % Mod;
        // REP(i, 1, n * 2) printf("%lld ", f[i]) ;puts("");
        printf("%lld\n", (f[n * 2 - 1] * power(inv2, n - 1)) % Mod);
        return 0;
    }
}

inline void DFS(int u, int fa)
{
    f[u][1] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        REP(j, 1, n) g[u][j] = 0;
        REP(j, 1, n) REP(k, 1, j - 1) g[u][j] = (g[u][j] + f[u][k] * f[v][j - k]) % Mod;
        int ret = 0;
        REP(j, 1, n) ret = (ret + f[v][j] * j) % Mod;
        REP(j, 1, n) f[u][j] = (g[u][j] + f[u][j] * ret) % Mod;
    }
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld", &n);
    // if ( n % 10 != 0 ) return Subtask1 :: main();
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(i, 1, n) 
    {
        int ret = 0;
        REP(j, 1, n) ret = (ret + f[i][j] * j) % Mod;
        printf("%lld %lld\n", i ,ret);
    }
    int ans = 0;
    REP(i, 1, n) ans = (ans + f[1][i] * i) % Mod;
    printf("%lld\n", ans);
    return 0;
}

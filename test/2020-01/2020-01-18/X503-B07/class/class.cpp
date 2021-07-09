/***************************************************************
	File name: class.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时00分24秒
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

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans;
int fac[maxn], inv[maxn], size[maxn], p[5010][5010];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int C(int n, int m) { return n >= m ? (fac[n] * inv[m] % Mod) * inv[n - m] % Mod : 0; }

inline void DFS(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS(v, u);
        size[u] += size[v]; 
        int x = size[v], y = n - size[v];
        REP(j, 1, 2 * m)
        {
            int ret = p[x][j] * p[y][2 * m - j] % Mod;
            ret = (ret * W[i] % Mod) * C(2 * m, j) % Mod;
            ret = ret * min(j, 2 * m - j) % Mod;
            ans = (ans + ret) % Mod;
        }
    }
}

signed main()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    int N = 2 * m;
    fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, n)
    {
        p[i][0] = 1;
        REP(j, 1, N) p[i][j] = p[i][j - 1] * i % Mod;
    }
    REP(i, 1, n - 1) 
    { 
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); 
        add(u, v, w); add(v, u, w);
    }
    DFS(1, 0);
    printf("%lld\n", ans);
    return 0;
}

/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年05月07日 星期四 15时55分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e3 + 10;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *f, int n, int inv)
{
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
            {
                int x = f[i + j], y = f[i + j + Mid] * sum % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

int f[maxn][maxn], g[maxn], n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int a[maxn], fac[maxn], inv[maxn], t[maxn], A[maxn], B[maxn], len;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void DFS(int u, int fa)
{
    REP(i, 0, m) f[u][i] = power(a[u], i);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        g[u] = (g[u] + g[v] - f[v][m] + f[v][m] * (1 - W[i])) % Mod;
        REP(j, 0, m) 
        {
            t[j] = f[u][j] * (1 - W[i]) % Mod;
            A[j] = f[u][j] * inv[j] % Mod;
            B[j] = f[v][j] * inv[j] % Mod;
        }

        fill(A + m + 1, A + len, 0); 
        fill(B + m + 1, B + len, 0); 
        NTT(A, len, 1); NTT(B, len, 1);
        REP(j, 0, len - 1) A[j] = A[j] * B[j] % Mod;
        NTT(A, len, -1);

        REP(j, 0, m) t[j] = (t[j] + (A[j] * fac[j] % Mod) * W[i]) % Mod;
        REP(j, 0, m) f[u][j] = t[j];
    }
    g[u] = (g[u] + f[u][m]) % Mod;
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld%lld", &n, &m);

    int N = 1000;
    fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    len = 1; while ( len <= (m << 1) ) len <<= 1;
    REP(i, 0, len - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (len >> 1) : 0);

    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1)
    {
        int u, v, x, y; scanf("%lld%lld%lld%lld", &u, &v, &x, &y);
        x = x * power(y, Mod - 2) % Mod;
        add(u, v, x); add(v, u, x);
    }
    DFS(1, 0);
    printf("%lld\n", (g[1] + Mod) % Mod);
    return 0;
}

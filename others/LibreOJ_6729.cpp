/***************************************************************
	File name: LibreOJ_6729.cpp
	Author: ljfcnyali
	Create time: 2020年07月29日 星期三 20时05分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int maxn = 1 << 18;
const int Mod = 998244353;

int n, m, a[21], inv[21];
vector<int> f, g;
bool Edge[21][21];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = (LL)r * a % Mod; a = (LL)a * a % Mod; b >>= 1; } return r; }

inline vector<int> FWT(vector<int> f, int op)
{
    REP(Mid, 0, n - 1)
        for ( int i = 0; i < (1 << n); i += (1 << Mid + 1) )
            REP(j, 0, (1 << Mid) - 1)
                f[i + (1 << Mid) + j] = (f[i + (1 << Mid) + j] + f[i + j] * op) % Mod;
    return f;
}

inline vector<int> ln(vector<int> g)
{
    vector<int> f[20]; REP(i, 0, n) f[i].resize(1 << n);
    REP(i, 0, (1 << n) - 1) f[__builtin_popcount(i)][i] = g[i];
    REP(i, 0, n) f[i] = FWT(f[i], 1);
    REP(i, 0, (1 << n) - 1) 
    {
        REP(j, 0, n) a[j] = f[j][i];
        f[0][i] = 0;
        REP(k, 1, n)
        {
            int ret = (LL)k * a[k] % Mod;
            REP(j, 1, k - 1) ret = (ret - ((LL)j * f[j][i] % Mod) * a[k - j]) % Mod;
            f[k][i] = (LL)inv[k] * ret % Mod;
        }
    }
    REP(i, 0, n) f[i] = FWT(f[i], -1);
    REP(i, 0, (1 << n) - 1) g[i] = f[__builtin_popcount(i)][i];
    return g;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); 
    REP(i, 1, n) inv[i] = inv(i);
    if ( n == 1 ) { puts("1"); return 0; }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[u][v] = Edge[v][u] = 1; }
    g.resize(1 << n);
    REP(i, 0, (1 << n) - 1)
    {
        int ret = 0;
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) 
            REP(k, j + 1, n) if ( (i >> k - 1) & 1 ) 
                ret += Edge[j][k];
        g[i] = power(2, ret);
    }
    f = ln(g);
    REP(i, 0, (1 << n) - 1) g[i] = 0;
    REP(i, 1, n)
    {
        REP(j, 0, (1 << n) - 1) if ( (j >> i - 1) & 1 ) 
            g[j ^ (1 << i - 1)] = f[j];
        g = ln(g);
        REP(j, 0, (1 << n) - 1) if ( !((j >> i - 1) & 1) )
            f[j ^ (1 << i - 1)] = g[j], g[j] = 0;
    }
    printf("%d\n", (f[(1 << n) - 1] + Mod) % Mod);
    return 0;
}

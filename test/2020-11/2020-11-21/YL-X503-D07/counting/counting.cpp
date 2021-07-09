/***************************************************************
	File name: counting.cpp
	Author: ljfcnyali
	Create time: 2020年11月21日 星期六 11时33分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, LL>
typedef long long LL;

const LL maxn = 1e6 + 10;
const LL Mod = 998244353;

LL N, n, m, a, b, p, v[maxn], f[18][18][18], inv[18], ans[maxn], C[20][20], cc[20][20];
int dp[2][1 << 18][18][18], cnt[1 << 18];
struct matrix { LL a[18 * 18][18 * 18]; } g, h;
matrix operator *(matrix a, matrix b)
{
    matrix c;
    REP(i, 0, N) REP(j, 0, N) 
    {
        c.a[i][j] = 0;
        REP(k, 0, N) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
    }
    return c;
}

inline LL power(LL a, LL b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline matrix power(matrix a, LL b)
{
    matrix r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
    return r;
}

inline LL get(LL t, LL x, LL y) { return x * (n - t + 1) + y; }

inline void Solve(LL t)
{
    mem(g.a); mem(h.a); g.a[1][get(t, t, 0)] = 1;
    N = get(t, t, n - t);
    REP(i, 0, t) REP(j, 0, n - t)   
    {
        REP(x, 0, i) REP(y, 0, j)
            h.a[get(t, i, j)][get(t, x, y)] = (h.a[get(t, i, j)][get(t, x, y)] + inv[i + j] * p % Mod * C[i][x] % Mod * C[j][y]) % Mod;
        REP(x, i, t) REP(y, j, n - t)
            h.a[get(t, i, j)][get(t, x, y)] = (h.a[get(t, i, j)][get(t, x, y)] + inv[n - i - j] * (1 - p) % Mod * C[t - i][t - x] % Mod * C[n - t - j][n - t - y]) % Mod;
    }
    if ( m ) g = g * power(h, m);
    REP(i, 0, t) REP(j, 0, n - t) f[t][i][j] = g.a[1][get(t, i, j)];
}

signed main()
{
    freopen("counting.in", "r", stdin);
    freopen("counting.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &a, &b); p = a * power(b, Mod - 2) % Mod;
    inv[0] = 1; REP(i, 1, n) inv[i] = inv[i - 1] * (Mod + 1) / 2 % Mod;
    REP(i, 0, n) C[i][0] = 1; REP(i, 1, n) REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
    REP(i, 0, (1 << n) - 1) 
    {
        scanf("%lld", &v[i]);
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ cnt[i];
    }
    REP(i, 0, n) Solve(i);

    REP(i, 0, n) REP(j, 0, i) cc[i][j] = power(C[i][j], Mod - 2);
    REP(x, 0, (1 << n) - 1)
    {
        if ( !v[x] ) continue ; LL t = cnt[x];
        REP(i, 0, t) REP(j, 0, n - t) 
            dp[0][x][i][j] = f[t][i][j] * cc[t][i] % Mod * cc[n - t][j] % Mod * v[x] % Mod;
    }
    int op = 0;
    REP(i, 1, n) 
    {
        op ^= 1;
        REP(x, 0, (1 << n) - 1) 
        {
            LL t = cnt[x];
            REP(a, 0, t) REP(b, 0, n - t)
                if ( (x >> i - 1) & 1 ) dp[op][x][a][b] = (dp[op ^ 1][x][a + 1][b] + dp[op ^ 1][x ^ (1 << i - 1)][a][b + 1]) % Mod;
                else dp[op][x][a][b] = (dp[op ^ 1][x][a][b] + dp[op ^ 1][x ^ (1 << i - 1)][a][b]) % Mod;
        }
    }
    REP(i, 0, (1 << n) - 1) printf("%lld ", (dp[op][i][0][0] + Mod) % Mod); puts("");
    return 0;
}

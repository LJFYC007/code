/***************************************************************
	File name: AgC038E.cpp
	Author: ljfcnyali
	Create time: 2021年01月27日 星期三 09时57分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 410;
const int Mod = 998244353;

int n, m, a[maxn], b[maxn], c[maxn], S, fac[maxn], inv[maxn], f[maxn][maxn], ans = 1, g[maxn][maxn][maxn][2], h[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int sgn(int x) { return x & 1 ? -1 : 1; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n); 
    REP(i, 1, n) { scanf("%lld%lld", &a[i], &b[i]); S += a[i]; } 
    REP(i, 1, n) c[i] = a[i] * power(S, Mod - 2) % Mod;
    REP(i, 1, n) REP(j, 0, b[i]) h[i][j] = power(c[i], j);
    g[0][0][0][0] = 1;
    REP(i, 1, n) 
    {
        REP(j, 0, S) REP(k, 0, m) REP(o, 0, 1) if ( g[i - 1][j][k][o] != 0 )
        {
            if ( o == 0 ) g[i][j][k + b[i] - 1][1] = (g[i][j][k + b[i] - 1][1] + g[i - 1][j][k][0] * h[i][b[i]] % Mod * C(k + b[i] - 1, b[i] - 1)) % Mod;
            g[i][j + a[i]][k][o] = (g[i][j + a[i]][k][o] + g[i - 1][j][k][o]) % Mod;
            REP(x, 0, b[i] - 1)
                g[i][j][k + x][o] = (g[i][j][k + x][o] - C(k + x, x) * h[i][x] % Mod * g[i - 1][j][k][o]) % Mod;
        }
        m += b[i];
    }
    REP(i, 0, S) REP(j, 0, m) 
    {
        int t = power(S, Mod - 2) * i % Mod;
        f[i][j] = (t + j) * power(power(1 - t, j + 2), Mod - 2) % Mod;
    }
    REP(j, 0, S) REP(k, 0, m) ans = (ans + f[j][k] * g[n][j][k][1]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

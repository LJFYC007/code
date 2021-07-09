/***************************************************************
	File name: LibreOJ_6495.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 19时56分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 30;

int n, Mod, fac[maxn], inv[maxn], f[maxn][maxn];
long double g[maxn][maxn], h[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &Mod);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    h[0] = 1; REP(i, 1, n) h[i] = h[i - 1] * i;
    f[1][1] = f[2][2] = g[1][1] = g[2][2] = 1;
    REP(i, 3, n) REP(j, 1, i)
    {
        int ret = 0;
        REP(x, 1, i - 1) REP(y, 1, j) ret = (ret + f[x][j - 1] * f[i - x][y] % Mod * C(i - 2, x - 1)) % Mod;
        REP(x, 1, i - 1) REP(y, 1, j - 2) ret = (ret + f[x][y] * f[i - x][j] % Mod * C(i - 2, x - 1)) % Mod;
        f[i][j] = ret;

        REP(x, 1, i - 1) REP(y, 1, j) g[i][j] += g[x][j - 1] * g[i - x][y] * h[i - 2] / h[x - 1] / h[i - x - 1]; 
        REP(x, 1, i - 1) REP(y, 1, j - 2) g[i][j] += g[x][y] * g[i - x][j] * h[i - 2] / h[x - 1] / h[i - x - 1];
    }
    long double x = 0; REP(i, 1, n) x += i * g[n][i];
    x = x / h[n - 1];
    printf("%lld\n", (int)(x + 0.5));
    int ans = 0; REP(i, 1, n) ans = (ans + i * f[n][i]) % Mod;
    printf("%lld\n", (ans * inv[n - 1] % Mod + Mod) % Mod);
    return 0;
}

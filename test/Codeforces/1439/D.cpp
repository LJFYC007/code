/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年11月18日 星期三 19时41分42秒
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

int f[maxn][maxn], g[maxn][maxn], n, m, Mod, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m >> Mod;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    f[0][0] = 1;
    REP(i, 1, n) 
    {
        REP(j, 1, i) 
        {
            f[i][i] = (f[i][i] + f[j - 1][j - 1] * f[i - j][i - j] % Mod * C(i - 1, j - 1) % Mod * (i + 1)) % Mod;
            g[i][i] = (g[i][i] + g[j - 1][j - 1] * f[i - j][i - j] % Mod * C(i - 1, j - 1) % Mod * (i + 1)) % Mod;
            g[i][i] = (g[i][i] + f[j - 1][j - 1] * g[i - j][i - j] % Mod * C(i - 1, j - 1) % Mod * (i + 1)) % Mod;
            g[i][i] = (g[i][i] + f[j - 1][j - 1] * f[i - j][i - j] % Mod * C(i - 1, j - 1) % Mod * (C(j, 2) + C(i - j + 1, 2))) % Mod;
        }

        REP(j, 0, i - 1)
        {
            f[i][j] = (f[i][j] + f[i - 1][j]) % Mod;            
            REP(len, 1, j) f[i][j] = (f[i][j] + f[i - len - 1][j - len] * f[len][len] % Mod * C(j, len)) % Mod;
            g[i][j] = (g[i][j] + g[i - 1][j]) % Mod;
            REP(len, 1, j) 
            {
                g[i][j] = (g[i][j] + f[i - len - 1][j - len] * g[len][len] % Mod * C(j, len)) % Mod;
                g[i][j] = (g[i][j] + g[i - len - 1][j - len] * f[len][len] % Mod * C(j, len)) % Mod;
            }
        }
    }
    printf("%lld\n", (g[n][m] + Mod) % Mod);
    return 0;
}

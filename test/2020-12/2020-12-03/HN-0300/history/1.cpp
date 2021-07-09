/***************************************************************
	File name: history.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 09时09分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int n, fac[maxn], inv[maxn], a[maxn], ans, f[310][310], g[310][310];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("history.in", "r", stdin);
    freopen("history1.out", "w", stdout);
    scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, n) scanf("%lld", &a[i]);
    
    for ( int len = n; len >= 2; -- len ) REP(i, 1, n - len + 1)
    {
        int j = i + len - 1;
        g[i][j] = fac[n - 1] * power(j - i, Mod - 2) % Mod;
        f[i][j] = (g[i][j] - g[i - 1][j] - g[i][j + 1] + g[i - 1][j + 1]) % Mod;
    }
    REP(o, 1, n)
    {
        int ret = 0;
        REP(i, 1, o) REP(j, o, n)
        {
            if ( 2 * j - i + 1 <= n ) ret = (ret + g[i][2 * j - i + 1] - g[i - 1][2 * j - i + 1]) % Mod;
            if ( 2 * i - j - 2 > 0 ) ret = (ret + g[2 * i - j - 2][j] - g[2 * i - j - 2][j + 1]) % Mod;
        }
        ans = (ans + ret * a[o]) % Mod;
    }
    printf("%lld\n", (ans * inv[n - 1] % Mod + Mod) % Mod);
    return 0;
}

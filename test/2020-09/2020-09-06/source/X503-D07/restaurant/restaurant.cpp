/***************************************************************
	File name: restaurant.cpp
	Author: ljfcnyali
	Create time: 2020年09月06日 星期日 10时06分34秒
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

int n, a[maxn], f[maxn], g[maxn], m, fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("restaurant.in", "r", stdin);
    freopen("restaurant.out", "w", stdout);
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); m += a[i]; }
    f[0] = 1;
    REP(i, 1, n) for ( int j = m; j >= a[i]; -- j ) f[j] = (f[j] - f[j - a[i]]) % Mod;
    REP(x, 1, n)
    {
        REP(j, 0, m) g[j] = f[j];
        for ( int j = a[x]; j <= m; ++ j ) g[j] = (g[j] + g[j - a[x]]) % Mod;
        int val = 0;
        REP(j, 0, m)
        {
            int ret = C(m, j + a[x]) * fac[j + a[x] - 1] % Mod;
            ret = ret * (a[x] * g[j] % Mod) % Mod;
            ret = ret * fac[m - j - a[x]] % Mod;
            val = (val + ret) % Mod;
        }
        REP(i, 1, n) if ( i != x ) val = val * power(a[i], Mod - 2) % Mod;
        ans = (ans + val) % Mod;
    }
    ans = ans * inv[m] % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

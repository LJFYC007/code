/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 11时01分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int tp, n, k, f[maxn], fac[maxn], inv[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return (n < m || n < 0 || m < 0) ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

inline int G(int i) { return C(n, n - i + 1) * (n - i + 1 - i + 1) % Mod; }

inline void Solve(int i)
{
    int ret = G(i);
    REP(x, i, n - i + 1) f[i] = (f[i] + C(n, x)) % Mod;
    f[i] = (f[i] - ret) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &tp);
    if ( tp == 1 ) scanf("%lld%lld", &n, &k);
    else scanf("%lld", &n);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

    int ans = 0;
    if ( tp == 1 ) 
    {
        Solve(k); Solve(k + 1);
        ans = (f[k] - f[k + 1]) % Mod;
    }
    else 
    {
        int x = 1;
        REP(i, 0, n / 2)
        {
            int ret = (G(i + 1) - G(i)) % Mod;
            ret = (ret + C(n, i)) % Mod;
            ret = (ret + C(n, n - i + 1)) % Mod;
            ans = (ans + x * ret) % Mod;
            x = x * 233 % Mod;
        }
    }

    /*
    REP(i, 0, n / 2) 
    {
        int ret = C(n, n - i + 1) * (n - i + 1 - i + 1) % Mod;
        REP(x, i, n - i + 1)
            f[i] = (f[i] + C(n, x)) % Mod;
        f[i] = (f[i] - ret) % Mod;
    }
    */

    // int ans = 0;
    // if ( tp == 1 ) ans = (f[k] - f[k + 1]) % Mod;
    // else REP(i, 0, n / 2) ans = (ans + power(233, i) * (f[i] - f[i + 1])) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

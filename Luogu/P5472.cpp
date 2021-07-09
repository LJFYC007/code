/***************************************************************
	File name: P5472.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 21时30分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int Mod = 998244353;

int f[4][4], n, m, q, type, a[maxn], g[maxn], inv;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int calc(int x)
{
    if ( x >= n - 2 ) return a[x];
    if ( type == 1 ) 
    {
        int d = (a[n] - a[n - 1]) % Mod;
        return (a[n] - d * (n - x)) % Mod;
    }
    int d1 = (a[n] - a[n - 1]) % Mod, d = (a[n] + a[n - 2] - 2 * a[n - 1]) % Mod;
    x = n - x;
    int ret1 = x * d1 % Mod, ret2 = x * (x - 1) % Mod * inv % Mod;
    return (a[n] - ret1 + (ret2 * d % Mod)) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &type);
    inv = power(2, Mod - 2);
    REP(i, 1, n) if ( type == 1 ) a[i] = i; else a[i] = (i * i) % Mod;
    REP(o, 1, m)
    {
        int x; scanf("%lld", &x);
        REP(i, x - 2, x) a[i] = calc(i);
        REP(i, 0, 2) REP(j, 0, 2) f[i][j] = 0;
        f[0][0] = 1;
        REP(i, 0, 2)
            REP(j, 0, 2)
            {
                if ( i + j > 2 ) break ; 
                if ( i < x ) 
                {
                    int ret = f[i][j] * (x - i) % Mod * power(n - i - j, Mod - 2) % Mod;
                    f[i + 1][j] = (f[i + 1][j] + ret) % Mod;
                    g[n - i - j] = (g[n - i - j] + ret * a[x - i]) % Mod;
                }
                if ( j < n - x ) 
                {
                    int ret = f[i][j] * (n - x - j) % Mod * power(n - i - j, Mod - 2) % Mod;
                    f[i][j + 1] = (f[i][j + 1] + ret) % Mod;
                    g[n - i - j] = (g[n - i - j] + ret * a[n - j]) % Mod;
                }
            }
        REP(i, n - 2, n) { a[i] = g[i]; g[i] = 0; }
    }
    scanf("%lld", &q); 
    REP(i, 1, q) { int x; scanf("%lld", &x); printf("%lld\n", (calc(x) + Mod) % Mod); }
    return 0;
}

/***************************************************************
	File name: P2606.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 20时17分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2000010;

int n, Mod, f[maxn], fac[maxn], inv[maxn], s[maxn];

inline int C(int n, int m) { return n >= m ? (fac[n] * inv[m] % Mod) * inv[n - m] % Mod : 1; }

inline int Lucas(int n, int m) { return m ? Lucas(n / Mod, m / Mod) * C(n % Mod, m % Mod) % Mod : 1; }

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &Mod);
    REP(i, 1, 2 * n + 1) s[i] = f[i] = 1;
    for ( int i = n; i >= 1; -- i ) s[i >> 1] += s[i];
    inv[0] = fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    for ( int i = n; i >= 1; -- i )
        f[i] = (Lucas(s[i] - 1, s[i << 1]) * f[i << 1] % Mod) * f[i << 1 | 1] % Mod;
    printf("%lld\n", f[1]);
    return 0;
}

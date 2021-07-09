/***************************************************************
	File name: P4921.cpp
	Author: ljfcnyali
	Create time: 2019年10月12日 星期六 07时36分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010; 
const int Mod = 998244353;

int fac[maxn], inv[maxn], T, n, ans, f[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline int C(int n, int m) { return (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int A(int n, int m) { return fac[n] * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fac[0] = 1; REP(i, 1, 1000) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 0, 1000) inv[i] = power(fac[i], Mod - 2);
    f[0] = 1; f[1] = 0;
    REP(i, 2, 1000) f[i] = 4 * i * (i - 1) * (f[i - 1] + (2 * i - 2) * f[i - 2] % Mod) % Mod;
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        REP(i, 0, n) printf("%lld\n", (power(2, i) * (C(n, i) * A(n, i)  % Mod) % Mod) * f[n - i] % Mod);
    }
    return 0;
}

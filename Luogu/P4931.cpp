/***************************************************************
	File name: P4931.cpp
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

const int maxn = 5000010; 
const int Mod = 998244353;

int fac[maxn], inv[maxn], T, n, f[maxn], k, p[maxn];

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
    fac[0] = 1; REP(i, 1, 5000000) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 0, 5000000) inv[i] = power(fac[i], Mod - 2);
    f[0] = p[0] = 1; f[1] = 0;
    REP(i, 2, 5000000) f[i] = 4 * (i * (i - 1) % Mod) * (f[i - 1] + (2 * i - 2) * f[i - 2] % Mod) % Mod;
    REP(i, 1, 5000000) p[i] = p[i - 1] * 2 % Mod;
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &k);
        int sum = C(n, k) * A(n, k) % Mod;
        sum = sum * (p[k] * f[n - k] % Mod) % Mod;
        printf("%lld\n", sum);
    }
    return 0;
}

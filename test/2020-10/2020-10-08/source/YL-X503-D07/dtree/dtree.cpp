/***************************************************************
	File name: dtree.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 10时42分47秒
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

int n, fac[maxn], inv[maxn], Mod, f[maxn], ans, inv2;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int calc(int n) { return (n + 1) * inv2 % Mod; }

signed main()
{
    freopen("dtree.in", "r", stdin);
    freopen("dtree.out", "w", stdout);
    scanf("%lld%lld", &n, &Mod);
    inv2 = power(2, Mod - 2);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod; 
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    int sum = 0;
    REP(i, 2, n) 
    {
        f[i] = 2 * sum % Mod;
        f[i] = f[i] * inv[i] % Mod;
        f[i] = f[i] * fac[i - 1] % Mod;
        sum = (sum + f[i] + calc(i - 1)) % Mod;
    }
    printf("%lld\n", (f[n] * fac[n] % Mod + Mod) % Mod);
    return 0;
}

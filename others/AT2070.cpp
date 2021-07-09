/***************************************************************
	File name: AT2070.cpp
	Author: ljfcnyali
	Create time: 2020年11月25日 星期三 21时26分49秒
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
const int Mod = 1e9 + 7;

int n, m, k, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &m, &k);
    int ans = 0, x = 1, y = 1;
    REP(i, 0, m + k)
    {
        int val = power(3, m + k - i) * C(n + i - 1, n - 1) % Mod;
        // x = 0; REP(j, max(0ll, i - k), m) x = (x + C(i, j)) % Mod;
        ans = (ans + val * x) % Mod;
        if ( i >= k + 1 ) { ans = (ans - val * y) % Mod; y = (y * 2 + C(i, i - k)) % Mod; }
        // REP(j, 0, i - k - 1) ans = (ans - val * C(i, j)) % Mod;
        x = (x * 2 - C(i, m)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

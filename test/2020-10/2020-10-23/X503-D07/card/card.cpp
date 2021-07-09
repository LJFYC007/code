/***************************************************************
	File name: card.cpp
	Author: ljfcnyali
	Create time: 2020年10月23日 星期五 08时55分01秒
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

int n, m, k, a[maxn], ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 0, 30)
    {
        m = 0;
        REP(j, 1, n) if ( (a[j] >> i) & 1 ) ++ m;
        int ret = 0;
        for ( int j = 1; j <= k; j += 2 ) 
            ret = (ret + C(m, j) * C(n - m, k - j)) % Mod;
        ans = (ans + ret * (1 << i)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

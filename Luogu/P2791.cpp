/***************************************************************
	File name: P2791.cpp
	Author: ljfcnyali
	Create time: 2020年07月26日 星期日 14时56分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 2e7 + 10;
const LL Mod = 998244353;

LL ans, N, M, S, L, n, m, k;
int fac[maxn], inv[maxn], p[maxn];

inline LL power(LL a, LL b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline LL C(LL n, LL m) { return n < m ? 0 : ((LL)fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( LL i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld%lld", &N, &M, &S, &L);

        
    // REP(i, 1, M) p[i] = power(i, L);

    REP(i, 1, S)
    {
        scanf("%lld%lld%lld", &n, &m, &k);
        ans = 0; LL ret;
        REP(x, 1, min(k, m))
        {
            ret = C(m, x) * C(n - m, k - x) % Mod;
            ans = (ans + ret * p[x]) % Mod;
        }
        ans = ans * power(C(n, k), Mod - 2) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}

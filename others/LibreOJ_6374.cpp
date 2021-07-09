/***************************************************************
	File name: LibreOJ_6374.cpp
	Author: ljfcnyali
	Create time: 2020年08月04日 星期二 20时46分17秒
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

int Tx, Ty, Mx, My, G, n, m, fac[maxn], inv[maxn], ans, f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld%lld", &Tx, &Ty, &Mx, &My);
    scanf("%lld%lld%lld", &m, &G, &n);
    REP(j, 0, m)
    {
        int sum1 = 0, sum2 = 0;
        REP(i, 0, j)
        {
            sum1 = (sum1 + sgn(i) * C(Tx - i * (Mx + 1) + j - 1, j - 1) * C(j, i)) % Mod;
            sum2 = (sum2 + sgn(i) * C(Ty - i * (My + 1) + j - 1, j - 1) * C(j, i)) % Mod;
        }
        f[j] = sum1 * sum2 % Mod;
        ans = (ans + sgn(m - j) * C(m, j) * f[j]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

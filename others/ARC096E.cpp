/***************************************************************
	File name: ARC096E.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 21时42分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3010;

int n, Mod, s[maxn][maxn], ans, fac[maxn], inv[maxn];

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &Mod);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2, Mod); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    s[0][0] = 1;
    REP(i, 1, n + 1) REP(j, 1, i) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % Mod;
    REP(i, 0, n) REP(j, 0, i)
    {
        int ret = sgn(i) * power(2, power(2, n - i, Mod - 1), Mod) * s[i + 1][j + 1] % Mod;
        ret = ret * C(n, i) % Mod;
        ret = ret * power(power(2, n - i, Mod), j, Mod) % Mod;
        ans = (ans + ret) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

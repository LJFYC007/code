/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 09时23分08秒
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
const int Mod = 1e9 + 7;

int n, k, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int calc(int n) { return C(2 * n, n) * power(n + 1, Mod - 2) % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &k);
    int ans = 0;
    REP(i, k, n) ans = (ans + C(2 * i - k - 1, i - 1)) % Mod;
    ans = ans * calc(k - 2) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

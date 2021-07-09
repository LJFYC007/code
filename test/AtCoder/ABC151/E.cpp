/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 20时25分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, a[maxn], fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) 
{ 
    if ( n < m ) return 0;
    return (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 0; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, n) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    REP(i, 1, n)
    {
        ans = (ans - C(n - i, m - 1) * a[i]) % Mod;
        // printf("%lld ", ans);
        ans = (ans + C(i - 1, m - 1) * a[i]) % Mod;
        // printf("%lld ", ans);
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

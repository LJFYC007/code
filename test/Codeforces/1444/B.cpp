/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年11月01日 星期日 19时29分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int n, a[maxn], ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n);
    REP(i, 1, 2 * n) scanf("%lld", &a[i]); 
    sort(a + 1, a + n + n + 1);
    ans = C(n + n, n);
    int sum = 0;
    REP(i, 1, n) sum += a[n + n - i + 1] - a[i];
    sum = sum % Mod;
    printf("%lld\n", (ans * sum) % Mod);
    /*
    REP(i, 1, n + n) REP(j, i + 1, n + n)
    {
        int sum = 0;
        REP(x, 1, n) REP(y, 1, n)
            sum += C(i - 1, n + x - y - 1) * C(n + n - j, n - x + y - 1);
        cout << i << " " << j << " " << sum << endl;
        ans = (ans + sum * (a[j] - a[i])) % Mod;
    }
    printf("%lld\n", ans);
    */
    return 0;
}

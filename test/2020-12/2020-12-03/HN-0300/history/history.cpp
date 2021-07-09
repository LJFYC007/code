/***************************************************************
	File name: history.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 09时09分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int n, a[maxn], ans, f[maxn], g[maxn], h[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve(int l, int r, int op)
{
    if ( l > r ) return 0;
    if ( op == 0 ) return (f[r] - (l >= 1 ? f[l - 1] : 0)) % Mod;
    if ( op == 1 ) return (g[r] - (l >= 1 ? g[l - 1] : 0)) % Mod;
    return (h[r] - (l >= 1 ? h[l - 1] : 0)) % Mod;
}

signed main()
{
    freopen("history.in", "r", stdin);
    freopen("history.out", "w", stdout);
    scanf("%lld", &n); 
    REP(i, 1, n) scanf("%lld", &a[i]);

    REP(i, 0, n) f[i] = (f[i - 1] + power(2 * i + 1, Mod - 2) - power(2 * i + 2, Mod - 2)) % Mod;
    REP(i, 0, n) g[i] = (g[i - 1] + i * (power(2 * i + 1, Mod - 2) - power(2 * i + 2, Mod - 2))) % Mod;
    REP(i, 0, n) h[i] = (h[i - 1] + power(2 * i + 2, Mod - 2)) % Mod;
    REP(i, 1, n)
    {
        int ret = 0, val1 = i - 1, val2 = (n - i - 1) / 2;
        ret = (ret + Solve(val1, val2, 0) * i + Solve(val1, val2, 2)) % Mod;
        if ( i != n ) 
        {
            ret = (ret + Solve(0, min(val1 - 1, val2), 0) + Solve(0, min(val1 - 1, val2), 1)) % Mod;
            ret = (ret + (n - 1) * Solve(max(val1, val2 + 1), (n - 2) / 2, 0) - 2 * Solve(max(val1, val2 + 1), (n - 2) / 2, 1)) % Mod;
            ret = (ret + Solve(max(val1, val2 + 1), (n - 2) / 2, 2)) % Mod;
        }
        ret = (ret + Solve(val2 + 1, min(n - i, val1 - 1), 0) * (n - i) - Solve(val2 + 1, min(n - i, val1 - 1), 1)) % Mod;
        ans = (ans + ret * a[i]) % Mod;
    }

    REP(i, 0, n) f[i] = (f[i - 1] + power(2 * i + 2, Mod - 2) - power(2 * i + 3, Mod - 2)) % Mod;
    REP(i, 0, n) g[i] = (g[i - 1] + i * (power(2 * i + 2, Mod - 2) - power(2 * i + 3, Mod - 2))) % Mod;
    REP(i, 0, n) h[i] = (h[i - 1] + power(2 * i + 3, Mod - 2)) % Mod;
    REP(i, 1, n)
    {
        int ret = 0, val1 = (i - 2) / 2, val2 = n - i - 1;
        ret = (ret + (i - 2) * Solve(val1, min(i - 3, val2), 0) - Solve(val1, min(i - 3, val2), 1)) % Mod;
        ret = (ret + Solve(0, min(val1 - 1, val2), 0) + Solve(0, min(val1 - 1, val2), 1)) % Mod;
        ret = (ret + (n - 2) * Solve(max(val1, val2 + 1), (n - 3) / 2, 0) - 2 * Solve(max(val1, val2 + 1), (n - 3) / 2, 1)) % Mod;
        ret = (ret + Solve(max(val1, val2 + 1), (n - 3) / 2, 2)) % Mod;
        ret = (ret + (n - i + 1) * Solve(val2 + 1, val1 - 1, 0)) % Mod;
        ret = (ret + Solve(val2 + 1, val1 - 1, 2)) % Mod;
        ans = (ans + ret * a[i]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

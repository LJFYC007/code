/***************************************************************
	File name: partition.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 10时04分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int N = 1e6;
const int Mod = 998244353;

int f[maxn][maxn], T, n, k, p[N + 10], inv[N + 10];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return ((p[n] * inv[m] % Mod) * inv[n - m]) % Mod; }

inline int calc(int n, int k)
{
    if ( k == 0 ) return 1; if ( k == 1 ) return n + 1;
    if ( k == 2 ) return (calc(n, k - 1) + n * (n - 1) / 2) % Mod;
    if ( n <= k ) return n < maxn ? f[n][n] : power(2, n);
    if ( n == k * 2 + 1 ) return 2 * k < maxn ? f[2 * k][2 * k] : power(2, 2 * k);
    if ( n < maxn && k < maxn ) return f[n][k] ? f[n][k] : f[n][k] = (calc(n, k - 1) + C(n, k)) % Mod; 
    return (calc(n, k - 1) + C(n, k)) % Mod;
}

inline int Solve(int x)
{
    int ret = ((x * x % Mod) * x) % Mod;
    ret = (ret + 3 * x * x) % Mod;
    ret = (ret + 8 * x) % Mod;
    return ret * power(6, Mod - 2) % Mod;
}

signed main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    f[0][0] = 1; REP(i, 1, maxn - 1) f[i][i] = (f[i - 1][i - 1] * 2) % Mod;
    p[0] = inv[0] = 1; REP(i, 1, N) p[i] = (p[i - 1] * i) % Mod;    
    inv[N] = power(p[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i) inv[i] = (inv[i + 1] * (i + 1)) % Mod;
    scanf("%lld", &T); 
    while ( T -- )  
    {
        int opt, n, k, l, r;
        scanf("%lld", &opt);
        if ( opt == 1 ) 
        { 
            scanf("%lld%lld", &n, &k);
            printf("%lld\n", calc(n, k)); 
        }
        else
        {
            scanf("%lld%lld%lld", &l, &r, &k);
            int ans = 0;
            if ( k == 1 ) 
            {
                ans = (l + r + 2) * (r - l + 1) % Mod;
                ans = ans * power(2, Mod - 2) % Mod;
            }
            else if ( k == 2 ) ans = (Solve(r) - Solve(l - 1) + Mod) % Mod;
            else REP(i, l, r) ans = (ans + calc(i, k)) % Mod;
            printf("%lld\n", ans);
        }
    }
    return 0;
}

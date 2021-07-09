/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年05月10日 星期日 15时22分44秒
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

int n, m, k, a, b, c, A, B, C, ans;
int fac[maxn], inv[maxn], deg[3];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int F(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int N = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    while ( ~scanf("%lld%lld%lld", &n, &m, &k) )
    {
        if ( ((n + m) & 1) || ((n + k) & 1) || ((m + k) & 1) ) { puts("0"); continue ; }
        ans = 0;
        REP(i, 0, n)
        {
            int a = i, A = n - i;
            int b = (m - n) / 2 + i, B = (n + m) / 2 - i;
            int c = (k - n) / 2 + i, C = (n + k) / 2 - i;
            if ( b + B != m || c + C != k ) continue ;
            if ( b < 0 || B < 0 || c < 0 || C < 0 ) continue ;
            int ret = 1;
            deg[0] = C + a;
            deg[1] = b + A;
            deg[2] = c + B;
            if ( deg[0] > 0 ) ret = ret * fac[deg[0] - 1] % Mod;
            if ( deg[1] > 0 ) ret = ret * fac[deg[1] - 1] % Mod;
            if ( deg[2] > 0 ) ret = ret * fac[deg[2] - 1] % Mod;
            ret = ret * (deg[0] * deg[2] - C * c) % Mod;
            ret = ret * F(n, a) % Mod;
            ret = ret * F(m, b) % Mod;
            ret = ret * F(k, c) % Mod;
            ret = ret * deg[1] % Mod;
            ans = (ans + ret) % Mod;
        }
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}

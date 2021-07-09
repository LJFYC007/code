/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2019年11月01日 星期五 15时29分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;
const int N = 1e5;
const int Mod = 998244353;

int n, m, k, ans, a[maxn], b[maxn], ret, fac[maxn], p[maxn], inv[maxn];
int f[maxn], dp[maxn], g[1010][1010];

inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r; 
}

inline int C(int n, int m) { return n >= m ? (fac[n] * inv[m] % Mod) * inv[n - m] % Mod : 0; }

inline void Solve()
{
    dp[0] = 1; REP(i, 1, m) f[i] = dp[i] = 0; 
    REP(i, 1, ret) REP(j, 1, m) f[j] = (f[j] + g[j][a[i]]) % Mod;
    REP(i, 1, m) REP(j, 1, i)
        dp[i] = (dp[i] + dp[i - j] * p[f[j]] % Mod * inv[i - j] % Mod * fac[i - 1] % Mod) % Mod;
    int w = 1, cnt = 0, sum = 0;
    REP(i, 1, ret)
    {
        if ( i > 1 && a[i] == a[i - 1] ) ++ sum; else sum = 1;
        w = w * power(sum, Mod - 2) % Mod;
        cnt += a[i]; w = w * C(cnt, a[i]) % Mod * fac[a[i] - 1] % Mod; 
    }
    ans = (ans + w * dp[m]) % Mod;
}

inline void DFS1(int x, int now)
{
    if ( x == n + 1 ) { ret = now; Solve(); return ; }
    ++ now;
    REP(i, a[now - 1], n - x + 1) { a[now] = i; DFS1(x + i, now); }
}

signed main()
{
    freopen("hybrid.in", "r", stdin);
    freopen("hybrid.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    if ( n > m ) swap(n, m);
    REP(i, 1, 1000) REP(j, 1, 1000) g[i][j] = __gcd(i, j);
    inv[0] = p[0] = fac[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 1, N) p[i] = p[i - 1] * k % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    a[0] = b[0] = 1; DFS1(1, 0);
    REP(i, 1, n) ans = ans * power(i, Mod - 2) % Mod;
    REP(i, 1, m) ans = ans * power(i, Mod - 2) % Mod;
    printf("%lld\n", ans);
    return 0;
}

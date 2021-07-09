/***************************************************************
	File name: square.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 15时42分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e6 + 10;
const int N = 4e6;
const int Mod = 998244353;

int n, m, ans, prime[maxn], tot, phi[maxn], f[maxn], g[maxn], h[maxn];
bool vis[maxn];
map<int, int> Map1, Map2, Map3;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get2(int x) { return x * x % Mod; }
inline int Get3(int x) { return Get2(x) * x % Mod; }
inline int Get4(int x) { return Get3(x) * x % Mod; }
inline int calc2(int x) { return x * (x + 1) / 2 % Mod; }
inline int calc3(int x) { return x * (x + 1) % Mod * (x + x + 1) % Mod * power(6, Mod - 2) % Mod; }
inline int calc4(int x) { return calc2(x) * calc2(x) % Mod; }

inline int Solve1(int n)
{
    if ( n <= N ) return h[n];
    if ( Map1.count(n) ) return Map1[n];
    int ret = calc2(n);
    for ( int i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret = (ret - Solve1(n / i) * (j - i + 1)) % Mod;
    }
    Map1[n] = ret; return ret;
}

inline int Solve2(int n)
{
    if ( n <= N ) return g[n];
    if ( Map2.count(n) ) return Map2[n];
    int ret = calc3(n);
    for ( int i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret = (ret - Solve2(n / i) * (calc2(j) - calc2(i - 1))) % Mod;
    }
    Map2[n] = ret; return ret;
}

inline int Solve3(int n)
{
    if ( n <= N ) return f[n];
    if ( Map3.count(n) ) return Map3[n];
    int ret = calc4(n);
    for ( int i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        ret = (ret - Solve3(n / i) * (calc3(j) - calc3(i - 1))) % Mod;
    }
    Map3[n] = ret; return ret;
}

signed main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    n = maxn - 10; phi[1] = 1;
    REP(i, 2, n) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    REP(i, 1, n) 
    {
        f[i] = (f[i - 1] + phi[i] * Get2(i)) % Mod;
        g[i] = (g[i - 1] + phi[i] * i) % Mod;
        h[i] = (h[i - 1] + phi[i]) % Mod;
    }

    scanf("%lld%lld", &n, &m);
    if ( n > m ) swap(n, m);

    int x = (30 + 36 * m + n) % Mod;
    x = (x + 54 * (n * m % Mod)) % Mod;
    x = (x - 31 * Get2(n)) % Mod;
    x = (x + 6 * m * Get2(n)) % Mod;
    x = (x - 4 * Get3(n)) % Mod;
    x = (x - 6 * m * Get3(n)) % Mod;
    x = (x + 4 * Get4(n)) % Mod;
    x = x * (n + 1) % Mod;
    x = x * n % Mod;
    x = x * power(-180, Mod - 2) % Mod;

    ans = 0;
    for ( int i = 1, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i); int k = n / i;
        int a = (3 * k + 3 * k * k) % Mod;
        int b = (-4 - 8 * k - 2 * m - 4 * k * m - 2 * n - 4 * n * k) % Mod;
        int c = (6 + 6 * m + 6 * n + 6 * n * m) % Mod;
        
        int val = 0;
        val = (val + a * (Solve3(j) - Solve3(i - 1))) % Mod;
        val = (val + b * (Solve2(j) - Solve2(i - 1))) % Mod;
        val = (val + c * (Solve1(j) - Solve1(i - 1))) % Mod;
        val = val * k % Mod * (1 + k) % Mod;
        val = val * power(12, Mod - 2) % Mod;
        ans = (ans + val) % Mod;
    }

    ans = (ans * 2 + x) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

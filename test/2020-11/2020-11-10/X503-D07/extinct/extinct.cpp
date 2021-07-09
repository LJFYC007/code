/***************************************************************
	File name: CF794G.cpp
	Author: ljfcnyali
	Create time: 2020年11月10日 星期二 20时23分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int Mod = 998244353;

int n, k, miu[maxn], prime[maxn], tot, fac[maxn], inv[maxn];
bool vis[maxn];
char s[2][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int calc(int n) { return (power(k, n + 1) - k) * power(k - 1, Mod - 2) % Mod; }

inline int Solve(int a, int b)
{
    if ( a == b && a == 0 )
    {
        int ret = 0;
        REP(d, 1, n) for ( int t = d; t <= n; t += d ) 
        {
            int x = power(k, d) * miu[t / d] * (n / t) % Mod;
            ret = (ret + x * (n / t)) % Mod;
        }
        return ret;
    }
    if ( a * b <= 0 ) return 0;
    if ( a == b ) return calc(n);
    a = abs(a); b = abs(b);
    return calc(n * __gcd(a, b) / max(a, b));
}

signed main()
{
    freopen("extinct.in", "r", stdin);
    freopen("extinct.out", "w", stdout);
    scanf("%s", s[0] + 1); scanf("%s", s[1] + 1); 
    n = maxn - 10; miu[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &k);

    int p = 0, q = 0, a = 0, b = 0;
    REP(i, 1, str(s[0] + 1))
    {
        if ( s[0][i] == 'A' ) ++ a;     
        if ( s[0][i] == 'B' ) -- b; 
        if ( s[0][i] == 'C' ) ++ p;
    }
    REP(i, 1, str(s[1] + 1))
    {
        if ( s[1][i] == 'A' ) -- a;     
        if ( s[1][i] == 'B' ) ++ b; 
        if ( s[1][i] == 'C' ) ++ q;
    }

    int ans = 0;
    REP(k, -q, p) ans = (ans + Solve(a + k, b + q - p + k) * C(p + q, p - k)) % Mod;
    
    if ( str(s[0] + 1) == str(s[1] + 1) )
    {
        REP(i, 1, str(s[0] + 1))
            if ( s[0][i] != 'C' && s[1][i] != 'C' && s[0][i] != s[1][i] ) goto Next ;
        int x = 0;
        REP(i, 1, str(s[0] + 1)) if ( s[0][i] == 'C' && s[1][i] == 'C' ) ++ x;
        ans = (ans - power(2, x) * Solve(0, 0)) % Mod;
        ans = (ans + power(2, x) * (calc(n) * calc(n) % Mod)) % Mod;
    }
Next : ;
    int num = 0; 
    REP(i, 1, str(s[0] + 1)) if ( s[0][i] != 'C' ) ++ num; 
    REP(i, 1, str(s[1] + 1)) if ( s[1][i] != 'C' ) ++ num; 
    ans = ans * power(2, num) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

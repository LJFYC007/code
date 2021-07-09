/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 09时25分21秒
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
const int N = 1e7;
const int M = 80000;
const int Mod = 1e9 + 7;

int n, k, d, prime[maxn], tot, miu[maxn], ans;
pii Prime[maxn];
bool vis[maxn];

inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r; 
}

inline int Getmiu(int x)
{
    if ( x <= N ) return miu[x];
    int ret = 0;
    REP(i, 1, tot)
    {
        if ( x % Prime[i].first != 0 ) continue ;
        ++ ret; x /= Prime[i].first;
        if ( x % Prime[i].first == 0 ) return 0;
    }
    if ( x > 1 ) ++ ret;
    return (ret & 1) ? -1 : 1;
}

inline int Getsum(int n, int d)
{
    if ( d == 1 ) { n %= Mod; return (n * (n + 1) / 2) % Mod; }
    int ret = d;
    int x = d - 1; x = x * x % Mod;
    ret = ret * power(x, Mod - 2) % Mod;
    int sum = (n % Mod) * power(d, (n + 1) % (Mod - 1)) % Mod;
    sum = (sum - (((n + 1) % Mod) * power(d, n % (Mod - 1)) % Mod)) % Mod;
    ret = ret * (sum + 1) % Mod;
    return ret;
}

inline void Solve(int p)
{
    int ret = Getmiu(p);
    if ( !ret ) return ;
    ret = ret * p % Mod;
    ret = ret * Getsum(n / p, power(d, p % (Mod - 1))) % Mod;
    ans = (ans + ret) % Mod;
}

inline void DFS1(int x, int sum)
{
    if ( x > tot ) { Solve(sum); return ; }
    DFS1(x + 1, sum);
    REP(i, 1, Prime[x].second)
    {
        sum = sum * Prime[x].first;
        DFS1(x + 1, sum);
    }
}

inline int mul(int a, int b, int Mod) 
{ 
    a %= Mod; b %= Mod;
    int r = 0;
    while ( b ) 
    {
        if ( b & 1 ) { r += a; if ( r > Mod ) r -= Mod; }
        a += a; if ( a > Mod ) a -= Mod;
        b >>= 1;
    }
    return r;
}

namespace Miller_Rabin
{
    const int N = 8, Prime[N] = {2, 3, 13, 17, 19, 23, 31, 37};

    inline int power(int a, int b, const int Mod) 
    { 
        int r = 1; 
        while ( b ) { if ( b & 1 ) r = mul(r, a, Mod); a = mul(a, a, Mod); b >>= 1; } 
        return r; 
    }

    inline bool Solve(int x, int p)
    {
        if ( x % p == 0 ) return false;
        if ( power(p, x - 1, x) != 1 ) return false;
        int k = x - 1;
        while ( !(k & 1) )
        {
            k >>= 1;
            int t = power(p, k, x);
            if ( t != 1 && t != x - 1 ) return false;
            if ( t == x - 1 ) break ; 
        }
        return true;
    }

    inline bool Check(int x)
    {
        if ( x == 1 ) return false;
        REP(i, 0, N - 1) if ( x == Prime[i] ) return true;
        REP(i, 0, N - 1) if ( !Solve(x, Prime[i]) ) return false;
        return true;
    }
}

namespace Pollard_Rho
{
    int ans;

    inline int Work(int n, int t)
    {
        int ret = 0, num = 1, v0 = rand() % (n - 1) + 1, v = v0, sum = 1;
        while ( 1 ) 
        {
            v = (mul(v, v, n) + t) % n;
            sum = mul(sum, abs(v - v0), n);
            if ( v == v0 || !sum ) return n;
            ++ ret;
            if ( ret == num || ret % 127 == 0 ) 
            {
                int d = __gcd(sum, n);
                if ( d != 1 ) return d;
                if ( ret == num ) { v0 = v; num <<= 1; }
            }
        }
    }

    inline void ReSolve(int n, int t)
    {
        if ( n == 1 || n <= ans ) return ;
        if ( Miller_Rabin :: Check(n) ) { ans = n; return ; }
        int x = n;
        while ( (x = Work(n, t --)) == n ) ;
        while ( n % x == 0 ) n /= x;
        ReSolve(x, t); ReSolve(n, t);
    }

    inline void Solve(int n)
    {
        tot = 0;
        for ( int i = 1; i <= M && prime[i] * prime[i] <= n; ++ i )
        {
            if ( n % prime[i] != 0 ) continue ;
            int x = prime[i], sum = 0;
            while ( n % x == 0 ) { n /= x; ++ sum; }
            Prime[++ tot] = pii(x, sum);
        }
        while ( n != 1 && !Miller_Rabin :: Check(n) ) 
        {
            ans = 0; ReSolve(n, 1000);
            int ret = 0;
            while ( n % ans == 0 ) { n /= ans; ++ ret; }
            Prime[++ tot] = pii(ans, ret);
        }
        if ( n > 1 ) Prime[++ tot] = pii(n, 1);
    }
}

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    srand(time(0));
    miu[1] = 1;
    REP(i, 2, N) 
    {
        if ( !vis[i] ) { miu[i] = -1; prime[++ tot] = i; }
        for ( int j = 1; j <= tot && i * prime[j] <= N; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    while ( ~scanf("%lld%lld%lld", &n, &k, &d) )
    {
        ans = 0; d %= Mod;
        Pollard_Rho :: Solve(k);
        DFS1(1, 1);
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}

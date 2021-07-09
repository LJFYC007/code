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

const int N = 1e7;
const int M = 80000;
const int Mod = 1e9 + 7;

inline int mul(const __int128 a, const __int128 b, const __int128 Mod) { return a * b % Mod; }

namespace Miller_Rabin
{
    const int N = 8, Prime[N] = {2, 3, 13, 17, 19, 23, 31, 37};

    inline int power(int a, int b, const int Mod) 
    { 
        int r = 1; 
        while ( b ) { if ( b & 1 ) r = mul(r, a, Mod); a = mul(a, a, Mod); b >>= 1; } 
        return r; 
    }

    inline bool Solve(int x, const int p)
    {
        if ( x % p == 0 ) return false;
        if ( power(p, x - 1, x) != 1 ) return false;
        int k = x - 1;
        while ( !(k & 1) )
        {
            k >>= 1;
            const int t = power(p, k, x);
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
    int ans = 1;

    inline int Work(int n, const int t)
    {
        int ret = 0, num = 1, v0 = rand() % (n - 1) + 1, v = v0, sum = 1;
        while ( 1 ) 
        {
            v = (mul(v, v, n) + t) % n;
            sum = mul(sum, abs(v - v0), n);
            if ( !sum ) return n;
            ++ ret;
            if ( ret == num || ret % 127 == 0 ) 
            {
                int d = __gcd(sum, n);
                if ( d != 1 ) return d;
                if ( ret == num ) { v0 = v; num <<= 1; }
            }
        }
        return n;
    }

    inline void ReSolve(int n, int t)
    {
        if ( n <= ans ) return ;
        if ( Miller_Rabin :: Check(n) ) { ans = n; return ; }
        int x = n;
        while ( (x = Work(n, t --)) == n ) ;
        while ( n % x == 0 ) n /= x;
        ReSolve(x, t); ReSolve(n, t);
    }

    inline int Solve(int n)
    {
        ans = 0; ReSolve(n, 100);
        return ans;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(time(0));
    int n; scanf("%lld", &n);
    while ( ~scanf("%lld", &n) )
    {
        if ( Miller_Rabin :: Check(n) ) puts("Prime");
        else printf("%lld\n", Pollard_Rho :: Solve(n));
    }
    return 0;
}

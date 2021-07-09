/***************************************************************
	File name: LibreOJ_143.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 15时16分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;


namespace Miller_Rabin
{
    const int N = 6, Prime[N] = {2, 3, 13, 17, 19, 23};
    const int INF = 1e9;

    inline int mul(int a, int b, int Mod)
    {
        if ( Mod <= INF ) return a * b % Mod;
        int r = 0;
        while ( b ) 
        {
            if ( b & 1 ) { r += a; if ( r > Mod ) r -= Mod; }
            a += a; if ( a > Mod ) a -= Mod;
            b >>= 1;
        }
        return r;
    }

    inline int power(int a, int b, int Mod) 
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

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int x;
    while ( ~scanf("%lld", &x) )
    {
        if ( Miller_Rabin :: Check(x) ) puts("Y");
        else puts("N");
    }
    return 0;
}

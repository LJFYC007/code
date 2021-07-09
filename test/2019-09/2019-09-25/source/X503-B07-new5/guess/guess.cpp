/***************************************************************
	File name: guess.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 16时23分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

int T, m, a, b, c;

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % m; a = (a * a) % m; b >>= 1; }
    return r;
}

inline int exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return a; }
    int d = exgcd(b, a % b, x, y);
    int t = x; x = y; y = t - (a / b) * y;
    return d;
}

inline bool Check(int x)
{
    while ( x > 1 ) { if ( x % 2 == 0 ) x /= 2; else return false; }
    return true;
}

signed main()
{
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &m, &a, &b, &c);
        if ( a == 1 ) { printf("%lld %lld %lld\n", (power(2, c) - 1 + m) % m, 1, 2); continue ; }
        if ( b == 1 ) { printf("%lld %lld %lld\n", 1, (power(2, c) - 1 + m) % m, 2); continue ; }
        if ( c == 1 ) { printf("%lld %lld %lld\n", 1, 1, 2); continue ; }
        if ( Check(m) ) { printf("%lld %lld %lld\n", m / 2, m / 2, m / 2); continue ; }
        int x, y, d = exgcd(c, a * b, x, y);
        y = -y; 
        while ( x < 0 || y < 0 ) y += c, x += a * b;
        printf("%lld %lld %lld\n", power(2, y * b), power(2, y * a), power(2, x));
    }
    return 0;
}

/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年06月05日 星期三 15时58分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef __int128 LL;

inline void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
    if ( !b ) { d = a; x = 1; y = 0; }
    else { exgcd(b, a % b, d, x, y); LL t = x; x = y; y = t - (a / b) * y; }
}

inline void read(LL &x)
{
    char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    x = 0;
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL n;
    read(n);
    LL ans, M, d, x, y, a, b, k;
    read(a); read(b);
    M = a; ans = b;
    REP(i, 2, n)
    {
        read(a); read(b);
        b = (b - ans % a + a) % a;
        exgcd(M, a, d, x, y); 
        k = x * (b / d) % a;
        ans += k * M;
        M = M / d * a;
        ans = (ans % M + M) % M;
    }
    printf("%lld\n", (long long)ans);
    return 0;
}

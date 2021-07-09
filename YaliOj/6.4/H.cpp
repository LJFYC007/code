/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2019年06月07日 星期五 15时05分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

inline void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
    if ( !b ) { d = a; x = 1; y = 0; }
    else { exgcd(b, a % b, d, x, y); LL t = x; x = y; y = t - (a / b) * y; }
}

inline void Solve(LL a, LL b, LL c)
{
    if ( c < 0 ) c += b;
    LL d, x, y;
    exgcd(a, b, d, x, y);
    if ( c % d != 0 ) { printf("Impossible\n"); return ; }
    a /= d; b /= d; c /= d;
    if ( b < 0 ) b = -b;
    x = ((c * x) % b + b) % b;
    printf("%lld\n", x);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL T; scanf("%lld", &T);
    while ( T -- ) 
    {
        LL n, d, x, y;
        scanf("%lld%lld%lld%lld", &n, &d, &x, &y);
        Solve(d, n, y - x);
    }
    return 0;
}

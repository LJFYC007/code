/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2019年06月05日 星期三 11时06分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

inline void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
    if ( b == 0 ) { d = a; x = 1; y = 0; return ; }
    exgcd(b, a % b, d, x, y);
    LL t = x; x = y; y = t - (a / b) * y;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL a, b; scanf("%lld%lld", &a, &b);
    LL x, y, d; exgcd(a, b, d, x, y);
    while ( x <= 0 ) x += b;
    while ( x > b ) x %= b;
    printf("%lld\n", x);
    return 0;
}
// ax - by = 1

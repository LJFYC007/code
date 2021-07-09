// luogu-judger-enable-o2
/***************************************************************
    File name: P3868.cpp
    Author: ljfcnyali
    Create time: 2019年06月09日 星期日 09时00分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

inline void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
    if ( !b ) { d = a; x = 1; y = 0; }
    else { exgcd(b, a % b, d, x, y); LL t = x; x = y; y = t - (a / b) * y; }
}

LL ans, a[20], b[20], n, B = 1;

inline LL power(LL a, LL b)
{
    LL r = 0;
    while ( b ) 
    {
        if ( b & 1 ) r = (r + a) % B;
        a = (a + a) % B;
        b >>= 1;
    }
    return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) { scanf("%lld", &b[i]); B *= b[i]; }
    REP(i, 1, n)
    {
        LL d, x, y;
        exgcd(B / b[i], b[i], d, x, y);
        x = (x % b[i] + b[i]) % b[i];
        a[i] = (a[i] % b[i] + b[i]) % b[i];
        ans = (ans + power(B / b[i] * x, a[i])) % B;
    }
    printf("%lld\n", ans);
    return 0;
}

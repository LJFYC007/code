/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年06月05日 星期三 14时38分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL Mod = 9901, num[1010], sum[1010], cnt, ans = 1;

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod;
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
    LL a, b; scanf("%lld%lld", &a, &b);
    for ( int i = 2; i * i <= a; ++ i )
        if ( a % i == 0 ) 
        {
            num[++ cnt] = i;
            while ( a % i == 0 ) { ++ sum[cnt]; a /= i; }
            sum[cnt] *= b;
        }
    if ( a > 1 ) { num[++ cnt] = a; sum[cnt] = b; }
    REP(i, 1, cnt)
    {
        LL x = power(num[i], sum[i] + 1) - 1, y = num[i] - 1;    
        y = power(y, Mod - 2);
        ans = (ans * (x * y) % Mod) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}

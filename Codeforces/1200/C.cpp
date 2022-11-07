/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 20时54分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, m, q, d;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d%I64d%I64d", &n, &m, &q);
    d = __gcd(n, m);
    REP(i, 1, q)
    {
        LL s1, s2, t1, t2; scanf("%I64d%I64d%I64d%I64d", &s1, &s2, &t1, &t2);
        -- s2; -- t2;
        LL x, y;
        if ( s1 == 1 ) x = s2 / (n / d);
        else x = s2 / (m / d);
        if ( t1 == 1 ) y = t2 / (n / d);
        else y = t2 / (m / d);
        if ( x == y ) puts("YES");
        else puts("NO");
    }
    return 0;
}

/***************************************************************
	File name: P1641.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 08时03分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, m, Mod = 20100403, ans;

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        b >>= 1; a = (a * a) % Mod;
    }
    return r;
}

inline LL C(LL a, LL b)
{
    LL sum = 1;
    REP(i, 2, a) sum = (sum * i) % Mod;
    LL sum1 = 1;
    REP(i, 2, a - b) sum1 = (sum1 * i) % Mod;
    REP(i, 2, b) sum1 = (sum1 * i) % Mod;
    sum = (sum * power(sum1, Mod - 2)) % Mod;
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    ans = C(n + m, m) - C(n + m, m - 1);
    ans = (ans % Mod + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}

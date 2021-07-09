/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月05日 星期三 14时26分03秒
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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL X, Y, m, n, l, x, y, d;
    cin >> X >> Y >> m >> n >> l;
    if ( n - m < 0 ) {swap(n, m), swap(X, Y); }
    exgcd(n - m, l, d, x, y);
    if ( (X - Y) % d != 0 || m == n ) { printf("Impossible\n"); return 0; }
    LL ans = x * (X - Y) / d;
    LL Mod = l / d;
    ans = (ans % Mod + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}

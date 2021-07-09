/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年06月05日 星期三 14时48分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;

LL n, ans, P = 1, a[maxn], b[maxn];

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
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld%lld", &a[i], &b[i]); P *= a[i]; }
    LL d, x, y;
    REP(i, 1, n)
    {
        LL Pi = P / a[i];
        exgcd(Pi, a[i], d, x, y);
        ans = ((ans + Pi * x * b[i]) % P + P) % P;
    }
    ans %= P;
    printf("%lld\n", ans);
    return 0;
}

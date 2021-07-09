/***************************************************************
	File name: P4446.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 16时26分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL n, p[maxn], prime[maxn], sum, Max = 32000, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 2, Max)
    {
        if ( !p[i] ) { p[i] = i; prime[++ sum] = i; }
        for ( LL j = 1; j <= sum && prime[j] * i <= Max; ++ j ) p[prime[j] * i] = prime[j];
    }
    REP(i, 1, 1000000) a[i] = i * i * i;
    scanf("%lld", &n);
    REP(i, 1, n)
    {
        LL x, p, ans = 1; scanf("%lld", &p);
        x = p;
        REP(k, 1, sum)
        {
            if ( prime[k] * prime[k] * prime[k] > x ) break ; 
            LL j = prime[k], y = j * j;
            while ( (x % j == 0) && ((x / j) % j == 0) && ((x / y) % j == 0) ) { ans *= j; x = (x / y) / j; }
            while ( x % j == 0 ) x /= j;
        }
        p = lower_bound(a + 1, a + 1000001, x) - a;
        if ( a[p] == x ) ans *= p;
        printf("%lld\n", ans);
    }
    return 0;
}

/***************************************************************
	File name: calc.cpp
	Author: ljfcnyali
	Create time: 2019年07月08日 星期一 09时40分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10000010;

int prime[maxn], sum, v[maxn];
LL l, r, Mod, ans, Max;

int main()
{
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    scanf("%lld%lld%lld", &l, &r, &Mod);
    Max = r;
    REP(i, 2, Max)
    {
        if ( !v[i] ) { v[i] = i; prime[++ sum] = i; }
        for ( LL j = 1; j <= sum && prime[j] * i <= Max; ++ j )
        {
            v[prime[j] * i] = prime[j];
            if ( i % prime[j] == 0 ) break ; 
        }
    }
    REP(i, 2, r)
    {
        if ( v[i] == i ) { ans = (ans + (r / i - (l - 1) / i)) % Mod; continue ; }
        int x = i, sum = 1, last = v[i];
        while ( x > 1 ) 
        {
            if ( v[x] != last ) { ++ sum; last = v[x]; }
            x /= v[x];
        }
        ans = (ans + sum * (r / i - (l - 1) / i)) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}

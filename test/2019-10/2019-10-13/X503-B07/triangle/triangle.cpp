/***************************************************************
	File name: triangle.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 09时44分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int Max = 1e7;

int n, l, prime[maxn], tot, p[maxn];

signed main()
{
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    REP(i, 2, Max)
    {
        if ( !p[i] ) prime[++ tot] = i, p[i] = i;
        for ( int j = 1; j <= tot && i * prime[j] <= Max; ++ j ) 
        {
            if ( i % prime[j] == 0 ) { p[i * prime[j]] = prime[j]; break ; }
            p[i * prime[j]] = prime[j];
        }
    }
    scanf("%lld", &n);
    while ( n -- ) 
    {
        scanf("%lld", &l); 
        if ( l % 2 == 0 ) l /= 2;
        int sum = 1;
        while ( p[l] > 1 )
        {
            int x = p[l], num = 0; 
            while ( l % x == 0 ) { ++ num; l /= x; }
            sum *= (num * 2 + 1);
        }
        printf("%lld\n", sum / 2);
    }
    return 0;
}

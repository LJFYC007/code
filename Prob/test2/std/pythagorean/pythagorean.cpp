/***************************************************************
	File name: pythagorean.cpp
	Author: ljfcnyali
	Create time: 2019年07月31日 星期三 12时45分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

inline LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

LL sum[5010];

int main()
{
    freopen("pythagorean.in", "r", stdin);
    freopen("pythagorean.out", "w", stdout);
    LL T, L, R; scanf("%lld", &T); 
    if ( T == 1 ) 
    {
        scanf("%lld%lld", &L, &R);
        LL ans = 0;
        REP(i, L, R)
        {
            for ( LL t = 1; t * t <= i; t += 2 ) 
            {
                LL s = sqrt(2 * i - t * t);
                if ( !(s & 1) || s * s + t * t != 2 * i || s <= t ) continue ;
                if ( gcd(s, t) != 1 ) continue ;
                ++ ans;
            }
        }
        printf("%lld\n", ans);
    }
    else
    {
        REP(a, 1, 5000) REP(b, a + 1, 5000) 
        { 
            LL c = sqrt(a * a + b * b); 
            if ( c * c == a * a + b * b && c <= 5000 && gcd(a, b) == 1 )
                ++ sum[c]; 
        }
        REP(i, 1, 5000) sum[i] += sum[i - 1];
        while ( T -- ) 
        {
            scanf("%lld%lld", &L, &R);
            printf("%lld\n", sum[R] - sum[max(L - 1, 0ll)]);
        }
    }
    return 0;
}

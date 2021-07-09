/***************************************************************
	File name: P4752.cpp
	Author: ljfcnyali
	Create time: 2019年06月13日 星期四 14时06分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

LL T, n, m, a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 1, m) scanf("%lld", &b[i]);
        sort ( a + 1, a + n + 1 );
        sort ( b + 1, b + m + 1 );
        if ( n == m ) { printf("NO\n"); continue ; }
        int now = 1;
        REP(i, 1, m)
        {
            while ( a[now] < b[i] && now <= n ) ++ now;
//            printf("%d %d\n", a[now], b[i]);
            if ( a[now] == b[i] && now <= n ) a[now ++] = 1;
        }
        sort ( a + 1, a + n + 1 );
        LL sum = 0;
//        REP(i, 1, n) printf("%lld ", a[i]);
        REP(i, 1, n) if ( a[i] != 1 && a[i] != 0 ) ++ sum;
//        printf("%lld\n", sum);
        if ( sum != 1 ) { printf("NO\n"); continue ; }
        sum = 0;
        LL x = a[n];
        for ( LL i = 2; i * i <= x; ++ i ) 
        {
            if ( x % i == 0 ) ++ sum;
            while ( x % i == 0 ) x /= i;
            if ( sum > 1 ) break ;
        }
        if ( x > 1 ) ++ sum;
        if ( sum > 1 ) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}

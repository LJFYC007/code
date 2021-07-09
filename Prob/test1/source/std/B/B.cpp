/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月15日 星期六 12时18分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL n, a[maxn], p, q, ans;
map<LL, int> Map;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &p, &q);
    REP(i, 1, n) { scanf("%lld", &a[i]); ++ Map[a[i]]; }
    REP(i, 1, n)
    {
        LL k = q - a[i];
        if ( k % p != 0 ) continue ; 
        k /= p;
        if ( k == a[i] ) continue ;
        ans += Map[k];
    }
    printf("%lld\n", ans);
    return 0;
}

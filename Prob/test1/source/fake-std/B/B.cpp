/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月18日 星期二 09时45分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL n, p, q, a[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    cin >> n >> p >> q;
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) REP(j, 1, n)
    {
        if ( a[i] == a[j] ) continue ;
        if ( a[i] + p * a[j] == q ) ++ ans;
    }
    printf("%lld\n", ans);
    return 0;
}

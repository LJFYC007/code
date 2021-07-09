/***************************************************************
	File name: P2261.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 15时28分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL n, k, ans; scanf("%lld%lld", &n, &k);
    ans = n * k;
    for ( LL l = 1, r; l <= n; l = r + 1)
    {
        if ( k / l != 0 ) r = min(k / (k / l), n);
        else r = n;
        ans -= (k / l) * (r - l + 1) * (l + r) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}

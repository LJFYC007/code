/***************************************************************
	File name: CF1151E.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 15时39分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

LL a[maxn], n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n)
    {
        scanf("%lld", &a[i]);
        ans += a[i] * (n - a[i] + 1);
        if ( i > 1 ) ans -= min(a[i], a[i - 1]) * (n - max(a[i], a[i - 1]) + 1);
    }
    printf("%lld\n", ans);
    return 0;
}

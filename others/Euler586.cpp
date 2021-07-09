/***************************************************************
	File name: Euler586.cpp
	Author: ljfcnyali
	Create time: 2020年10月20日 星期二 21时45分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, r, ans;

inline int Check(int n)
{
    int cur = 0;
    REP(a, ceil(n * 21.0 / 5), 9 * n)
    {
        int x = sqrt(a);
        if ( x * x == a ) ++ cur;
    }
    return cur;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &r);
    REP(i, 1, n) if ( Check(i) == r ) ++ ans;
    printf("%lld\n", ans);
    return 0;
}

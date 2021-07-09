/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 20时26分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 2e18;

int x, y, ans = INF;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &x, &y);
    if ( x >= y ) { printf("%lld\n", x - y); return 0; }
    ans = y - x;

    int sum = 0;
    while ( x <= INF ) 
    {
        int num = abs(x - y), val = sum;         
        for ( int j = 0, k; j < sum; ++ j ) if ( (num >> j) & 1 )
        {
            k = j; num -= (1ll << j);
            while ( k + 1 < sum && (num >> k + 1) & 1 ) { num -= (1ll << k + 1); ++ k; }
            if ( k == j ) ++ val;
            else val += 2;
        }
        ans = min(ans, (num / (1ll << sum)) + val);
        x = x * 2; ++ sum;
    }
    printf("%lld\n", ans);
    return 0;
}

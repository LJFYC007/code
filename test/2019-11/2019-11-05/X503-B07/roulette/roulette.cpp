/***************************************************************
	File name: roulette.cpp
	Author: ljfcnyali
	Create time: 2019年11月05日 星期二 10时58分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 40;

int T, n, w, a[maxn];

namespace Subtask1 
{
    inline void main()
    {
        int x = w / (37 - n);
        printf("%lld\n", max(0ll, x * 36 - x * (37 - n)));
    }
}

namespace Subtask2
{
    inline long double Solve()
    {
        int x = w / (37 - n), num = 37 - n;
        REP(i, 1, n) x = min(x, a[i]);
        REP(i, 1, n) if ( a[i] == x ) ++ num;
        long double sum = (37 - n) * 1.0 / num * x * 36;
        return sum - x * (37 - n);
    }

    inline void main()
    {
        long double ans = 0;
        ans = max(ans, Solve());
        int tot = 0;
        REP(i, 1, w)
        {
            int ret = (37 - n) * i, num = 37 - n;
            REP(j, 1, n) if ( a[j] <= i ) { ret += i - a[j]; ++ num; }
            if ( ret > w ) break ; ++ tot; if ( tot > 100000 ) break ; 
            long double sum = (37 - n) * 1.0 / num * i * 36;
            REP(j, 1, n) if ( a[j] <= i ) { sum += 1.0 / num * (i - a[j]) * 36; }
            ans = max(ans, sum - ret);
        }
        printf("%.7Lf\n", ans);
    }
}

signed main()
{
    freopen("roulette.in", "r", stdin);
    freopen("roulette.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &w, &n);
        bool flag = true;
        REP(i, 1, n) { scanf("%lld", &a[i]); if ( a[i] <= w ) flag = false; }
        if ( n <= 1 ) { puts("0"); continue ; }
        if ( flag == true ) { Subtask1 :: main(); continue ; }
        Subtask2 :: main();
    }
    return 0;
}

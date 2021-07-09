/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月06日 星期六 09时06分46秒
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

int n, l[maxn], r[maxn], ans;
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
#endif
    scanf("%lld%s", &n, s);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]); 
    ans = 0;
    REP(i, 1, n) REP(j, l[i] + 1, r[i]) REP(x, 1, n) REP(y, l[x] + 1, r[x])
    {
        if ( j <= 0 && y <= 0 )
        {
            int Max = -100;
            REP(k, min(i, x) + 1, max(i, x) - 1) Max = max(Max, l[k] + 1);
            if ( j < Max && y < Max ) 
                continue ;
        }
        if ( j > 0 && y > 0 )
        {
            int Max = 100;
            REP(k, min(i, x) + 1, max(i, x) - 1) Max = min(Max, r[k]);
            if ( Max < j && Max < y ) 
                continue ;
        }
        ans += abs(x - i) + abs(y - j);
    }
    printf("%lld\n", ans);
    return 0;
}

/***************************************************************
	File name: P2429.cpp
	Author: ljfcnyali
	Create time: 2019年06月08日 星期六 14时17分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

map<LL, bool> Map;

LL n, m, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m); 
    LL Mod = 376544743;
    REP(i, 1, n)
    {
        LL x, now; scanf("%lld", &x);
        now = x;
        while ( now <= m )
        {
            if ( !Map[now] ) { Map[now] = true; ans += now; ans %= Mod; }
            now += x;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

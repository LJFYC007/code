/***************************************************************
	File name: monster.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 09时27分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;

int n, m, h[maxn], num;

signed main()
{
    freopen("monster.in", "r", stdin);
    freopen("monster.out", "w", stdout);
    scanf("%lld", &n); num = n;
    REP(i, 0, n - 1) scanf("%lld", &h[i]);
    scanf("%lld", &m);
    REP(i, 1, m)
    {
        int x, y; scanf("%lld%lld", &x, &y);
        REP(j, 0, n - 1) if ( (j & x) == j ) printf("%lld ", j); puts("");
        REP(j, 0, n - 1) if ( h[j] > 0 && (j & x) == j ) { h[j] -= y; if ( h[j] <= 0 ) -- num; }
        printf("%lld\n", num);
    }
    return 0;
}


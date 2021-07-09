/***************************************************************
	File name: lock.cpp
	Author: ljfcnyali
	Create time: 2020年09月03日 星期四 21时43分48秒
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

int n, m, a[maxn], ans;

signed main()
{
    freopen("lock.in", "r", stdin);
    freopen("lock.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 0, (1 << n) - 1)
    {
        int sum = 0;
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) sum += a[j];
        if ( sum >= m ) continue ;
        bool flag = true;
        REP(j, 1, n) if ( !((i >> j - 1) & 1) ) flag &= (sum + a[j] >= m);
        if ( flag == true ) ++ ans;
    }
    if ( ans == 0 ) ans = 1;
    printf("%lld\n", ans);
    return 0;
}

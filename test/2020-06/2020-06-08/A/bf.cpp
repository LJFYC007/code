/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月08日 星期一 08时33分44秒
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

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]);
    for ( int i = 62; i >= 0; -- i ) 
    {
        ans |= (1ll << i);
        bool flag = true;
        REP(j, 1, n)
        {
            bool f = false;
            REP(k, l[j], r[j]) if ( (k & ans) == ans ) { f = true; break ; }
            if ( !f ) { flag = false; break ; }
        }
        if ( !flag ) ans ^= (1ll << i);
    }
    printf("%lld\n", ans);
    return 0;
}

/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月08日 星期一 08时00分03秒
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
            int x = (l[j] | ans);
            for ( int k = 62; k >= 0; -- k )  
            {
                if ( ((x >> k) & 1) && !((ans >> k) & 1) && x - (1ll << k) >= l[j] )
                    x -= (1ll << k);
                if ( x <= r[j] ) break ; 
            }
            if ( x > r[j] ) { flag = false; break ; }
        }
        if ( !flag ) ans ^= (1ll << i);
    }
    printf("%lld\n", ans);
    return 0;
}

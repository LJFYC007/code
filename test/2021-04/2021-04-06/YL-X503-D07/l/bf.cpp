/***************************************************************
    File name: l.cpp
    Author: ljfcnyali
    Create time: 2021年04月06日 星期二 10时58分33秒
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
 
int a, b, T, ans, n;
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("l.in", "r", stdin);
    freopen("l.out", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &a, &b); ans = -1; n = 0;
        REP(i, 0, 100000)
        {
            int x = __gcd(i * i * i + b, (a + i) * (a + i) * (a + i) + b);
            if ( x > ans ) { ans = x; n = i; } 
        }
		cout << ans << " ";
        printf("%lld\n", n);
    }
    return 0;
}

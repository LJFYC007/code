/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 21时03分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, a, b, n, S;
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &a, &b, &n, &S);
        int x, y;
        if ( a * n >= S ) x = S / n * n;
        else x = a * n;
        y = S - x;
        if ( y <= b ) puts("YES");
        else puts("NO");
    }
    return 0;
}

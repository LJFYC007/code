/***************************************************************
	File name: T103286.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 15时50分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int a, b, x, y, ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &a, &b);
    if ( a * a == 4 * b ) { puts("inf"); return 0; } 
    REP(A, 0, max(a / 2, (int)sqrt(b)))
    {
        int X = b - A * A, Y = 2 * A - a;
        if ( Y == 0 ) Y = 1;
        if ( X % Y == 0 )
        {
            x = X / Y; int t = x * x + a * x + b; y = sqrt(t); 
            if ( y * y == t && x >= 0 && y >= 0 ) ++ ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

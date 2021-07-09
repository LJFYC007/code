/***************************************************************
	File name: ARC103D.cpp
	Author: ljfcnyali
	Create time: 2021年01月27日 星期三 19时31分21秒
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

int n, a[maxn], b[maxn], m = 40;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); int num1 = 0, num2 = 0;
    REP(i, 1, n) { scanf("%lld%lld", &a[i], &b[i]); if ( a[i] + b[i] & 1 ) ++ num1; else ++ num2; } 
    if ( num1 && num2 ) { puts("-1"); return 0; }
    printf("%lld\n", m);
    if ( num2 ) { printf("1 "); m --; REP(i, 1, n) -- a[i]; }
    for ( int i = m - 1; i >= 0; -- i ) printf("%lld ", (1ll << i)); puts("");
    REP(i, 1, n)
    {
        if ( num2 ) printf("R");
        int x = 0, y = 0;
        for ( int j = m - 1; j >= 0; -- j )
        {
            int len = 1ll << j;
            if ( abs(a[i] - x) > abs(b[i] - y) )
            {
                if ( x < a[i] ) { x += len; printf("R"); }
                else { x -= len; printf("L"); }
            }
            else
            {
                if ( y < b[i] ) { y += len; printf("U"); }
                else { y -= len; printf("D"); }
            }
        }
        puts("");
    }
    return 0;
}

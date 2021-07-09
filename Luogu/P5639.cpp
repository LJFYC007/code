/***************************************************************
	File name: P5639.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 19时08分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, ans, x, y = 1;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%d", &x);
        if ( x != y ) ++ ans;
        y = x;
    }
    printf("%d\n", ans);
    return 0;
}

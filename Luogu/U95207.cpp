/***************************************************************
	File name: U95207.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 14时06分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int ans = -1, x;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    char c = getchar();
    while ( c == '0' || c == '1' ) 
    {
        if ( c == '0' ) ++ x;
        else -- x;
        ans = ans > x ? ans : x; 
        if ( x == -1 ) x = 0;
        c = getchar();
    }
    printf("%d\n", ans);
    return 0;
}

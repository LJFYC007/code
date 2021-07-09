/***************************************************************
	File name: P5098.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 19时55分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int Max1, Max2, Min1, Min2, n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Min1 = Min2 = 0x3f3f3f3f;
    scanf("%d", &n);
    REP(i, 1, n) 
    {
        int x, y; scanf("%d%d", &x, &y);
        Max1 = max(Max1, x + y);
        Max2 = max(Max2, x - y);
        Min1 = min(Min1, x + y);
        Min2 = min(Min2, x - y);
    }
    printf("%d\n", max(Max1 - Min1, Max2 - Min2));
    return 0;
}

/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 08时17分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    REP(n, 1, 120)
    {
        int ans = 0;
        REP(y, n + 1, 10000000)
        {
            if ( (n * y) % (y - n) == 0 ) ++ ans;
        }
        printf("%d %d\n", n, ans);
    }
    return 0;
}

/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 11时04分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

signed main()
{
    freopen("point.in", "w", stdout);
    int n = 500000;
    printf("%lld\n", n);
    int i = 1, sum = 0; 
    srand(time(0));
    while ( i < n ) 
    {
        if ( n - i <= 2000 ) 
        {
            REP(j, i, n) { ++ sum; printf("%lld ", (long long)rand() % 100000 + 1); }
            if ( sum < n ) { printf("%lld ", (long long)rand() % 10000 + 1); }
            return 0; 
        }
        int x = rand() % 1000 + 1;
        int p = rand() % 10 + 2;
        REP(j, i, i + x)
        {
            int y = ((long long)rand() % 10000000 + 1);
            printf("%lld ", p * y);
            ++ sum;
        }
        i += x + 1;
    }
    return 0;
}

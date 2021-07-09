/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 11时04分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("complex.in", "w", stdout);
    int n = 10;
    srand(time(0));
    printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 10 + 1); puts("");
    int last = n;
    REP(i, 1, 5)
    {
        last = rand() % last + 1;
        printf("%d ", last == 1 ? 2 : last);
    }
    REP(i, 6, n)
    {
        if ( i % 100000 == 0 ) last = rand() % last + 1;
        printf("%d ", last == 1 ? 2 : last);
    }
    puts("");
    return 0;
}

/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年07月11日 星期四 09时21分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("div.in", "w", stdout);
    srand(time(0));
    LL m = 200, n = 1000000000;
    LL x = rand() * rand() % n + 1;
    printf("%lld %lld\n", n, m);
    REP(i, 1, m) printf("%lld ", (rand() % 2 == 0) ? (x * (rand() % 100 + 1)) % n + 1 : rand() % n + 1);
    return 0;
}

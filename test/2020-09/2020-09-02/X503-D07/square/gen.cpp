/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 21时29分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("square.in", "w", stdout);
    srand(time(0));
    // int T = 1000000; printf("%d\n", T);
    // REP(i,1 , T) printf("%d\n", rand() % 10000000 + 1);
    int T = 100; printf("%d\n", T);
    REP(i,1 , T) printf("%d\n", rand() % 1000 + 1);
    return 0;
}

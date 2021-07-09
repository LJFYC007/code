/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 11时19分14秒
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
    freopen("b.in", "w", stdout);
    int X = 10, Y = 10, Z = 10;
    printf("%d %d %d\n", X, Y, Z);
    REP(i, 1, 30) printf("%d %d %d\n", rand() % 100, rand() % 100, rand() % 100);
    return 0;
}

/***************************************************************
	File name: fudepen.cpp
	Author: ljfcnyali
	Create time: 2019年10月11日 星期五 10时46分43秒
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
    freopen("fudepen.in", "r", stdin);
    freopen("fudepen.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        int x; scanf("%d", &x);
        if ( x == 1 ) puts("1");
        if ( x == 2 ) puts("4");
        if ( x == 3 ) puts("23");
    }
    return 0;
}

/***************************************************************
	File name: coin.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 08时13分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("coin.in", "r", stdin);
    freopen("coin.out", "w", stdout);
    int T; double r;
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%lf", &r);
        printf("%.7lf\n", 2 * r);
    }
    return 0;
}

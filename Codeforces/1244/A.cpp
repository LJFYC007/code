/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 16时48分38秒
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
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T;
    int a, b, c, d, e;
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        int num = (a - 1) / c + 1;    
        if ( (e - num) * d >= b ) printf("%d %d\n", num, e - num);
        else puts("-1");
    }
    return 0;
}

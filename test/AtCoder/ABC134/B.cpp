/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时02分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, d;
    scanf("%d%d", &n, &d);
    int x = n / (2 * d + 1);
    if ( x * (2 * d + 1) < n ) ++ x;
    printf("%d\n", x);
    return 0;
}

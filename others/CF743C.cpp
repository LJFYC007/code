/***************************************************************
	File name: CF743C.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 15时29分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; scanf("%d", &n);
    if ( n == 1 ) puts("-1");
    else printf("%d %d %d\n", n, n + 1, n * (n + 1));
    return 0;
}

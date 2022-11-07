/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 17时03分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int b, g, n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &b, &g, &n);
    REP(i, 0, n)
        if ( i <= b && (n - i) <= g ) ++ ans;
    printf("%d\n", ans);
    return 0;
}

/***************************************************************
	File name: CF1237E.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 11时09分33秒
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
    int x = 1, n;
    scanf("%d", &n);
    while ( x <= n )
    {
        if ( x == n || x + 1 == n ) { puts("1"); return 0; }
        if ( x & 1 ) x = 2 * (x + 1);
        else x = 2 * x + 1;
    }
    puts("0");
    return 0;
}

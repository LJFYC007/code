/***************************************************************
	File name: P2397.cpp
	Author: ljfcnyali
	Create time: 2019年06月13日 星期四 15时04分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

map<int, int> Map;
int n, x, m = -1, cnt;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    m = n / 2;
    REP(i, 1, n)
    {
        scanf("%d", &x);
        if ( cnt == 0 ) m = x;
        if ( x == m ) ++ cnt;
        else -- cnt;
    }
    printf("%d\n", m);
    return 0;
}

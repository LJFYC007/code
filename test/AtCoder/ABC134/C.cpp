/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时08分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Max, Maxx, n, k1;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);    
    REP(i, 1, n) 
    { 
        int x; scanf("%d", &x); 
        if ( x >= Max ) { Maxx = Max; Max = x; k1 = i; continue ; }
        else if ( x > Maxx ) { Maxx = x; }
    }
    REP(i, 1, n)
    {
        if ( k1 == i ) printf("%d\n", Maxx);
        else printf("%d\n", Max);
    }
    return 0;
}

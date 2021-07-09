/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时57分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int a[55][11000], s[55];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("haha1.out", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int x = 0, y = 1;
    REP(i, 1, 10775)
    {
        int val; scanf("%d", &val);
        if ( val == 1 && i != 3 ) { s[x] = y; ++ x; y = 1; a[x][y] = val; }
        else { ++ y; a[x][y] = val; }
    }
    s[50] = y;
    printf("a = {");
    REP(i, 1, 50) { printf("{%d", a[i][1]); REP(j, 2, s[i]) printf(",%d", a[i][j]); printf("},\n"); }
    return 0;
}

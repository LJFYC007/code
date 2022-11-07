/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 14时53分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int x[7], y[7];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 1, 6) scanf("%d%d", &x[i], &y[i]);
    if ( x[5] <= x[1] && x[2] <= x[6] && y[5] <= y[1] && y[2] <= y[6] ) { printf("NO\n"); return 0; }
    if ( x[3] <= x[1] && x[2] <= x[4] && y[3] <= y[1] && y[2] <= y[4] ) { printf("NO\n"); return 0; }
    bool flag = false;
    if ( x[3] <= x[1] && x[2] <= x[4] ) 
    {
        if ( y[4] >= y[2] && y[3] <= y[2] ) { y[2] = y[3]; flag = true; }
        else if ( y[4] >= y[1] && y[3] <= y[1] ) { y[1] = y[4]; flag = true; }
    }
    if ( y[3] <= y[1] && y[2] <= y[4] ) 
    {
        if ( x[4] >= x[2] && x[3] <= x[2] ) { x[2] = x[3]; flag = true;  }
        else if ( x[4] >= x[1] && x[3] <= x[1] ) { x[1] = x[4]; flag = true; }
    }
    if ( x[5] <= x[1] && x[2] <= x[6] && y[5] <= y[1] && y[2] <= y[6] ) { printf("NO\n"); return 0; }
    if ( flag ) { puts("YES"); return 0; }
    swap(x[3], x[5]); swap(x[4], x[6]);
    swap(y[3], y[5]); swap(y[4], y[6]);
    if ( x[3] <= x[1] && x[2] <= x[4] ) 
    {
        if ( y[4] >= y[2] && y[3] <= y[2] ) y[2] = y[3];
        else if ( y[4] >= y[2] && y[3] <= y[2] ) y[1] = y[4];
    }
    if ( y[3] <= y[1] && y[2] <= y[4] ) 
    {
        if ( x[4] >= x[2] && x[3] <= x[2] ) x[2] = x[3];
        else if ( x[4] >= x[1] && x[3] <= x[1] ) x[1] = x[4];
    }
    if ( x[5] <= x[1] && x[2] <= x[6] && y[5] <= y[1] && y[2] <= y[6] ) { printf("NO\n"); return 0; }
    puts("YES");
    return 0;
}

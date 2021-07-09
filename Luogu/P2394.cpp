/***************************************************************
	File name: P2394.cpp
	Author: ljfcnyali
	Create time: 2019年06月17日 星期一 14时42分05秒
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
    long double x;
    scanf("%15Lf", &x);
    printf("%.8Lf", x / 23.0);
    return 0;
}

/***************************************************************
	File name: P3978.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 19时27分02秒
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
    double n; cin >> n;
    printf("%.12lf\n", n * (n + 1) / (2 * (2 * n - 1)));
    return 0;
}

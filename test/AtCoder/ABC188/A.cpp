/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 19时51分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int x, y; cin >> x >> y;
    if ( x > y ) swap(x, y);
    if ( x + 3 > y ) puts("Yes");
    else puts("No");
    return 0;
}
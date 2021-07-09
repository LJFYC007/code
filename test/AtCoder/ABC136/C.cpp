/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时58分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int a[100010], n;

int main()
{
    scanf("%d", &n);
    int sum = 0;
    REP(i, 1, n) scanf("%d", &a[i]);
    for ( int i = n; i >= 2; -- i )
    {
        if ( a[i] < a[i - 2] ) -- a[i - 1];
    }
    REP(i, 1, n - 1) if ( a[i] > a[i + 1] ) { puts("No\n"); return 0; }
    puts("Yes");
    return 0;
}

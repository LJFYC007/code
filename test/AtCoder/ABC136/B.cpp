/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时57分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    int n, ans = 0; scanf("%d", &n);
    REP(i, 1, n)
    {
        int x = i, sum = 0;
        while ( x > 0 ) { x /= 10; ++ sum; }  
        if ( sum % 2 == 1 ) ++ ans;
    }
    printf("%d\n", ans);
    return 0;
}

/***************************************************************
	File name: P3599.cpp
	Author: ljfcnyali
	Create time: 2019年07月12日 星期五 20时19分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int x, T, n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &x, &T);
    if ( x == 1 )
    {
        while ( T -- )
        {
            scanf("%d", &n);
            if ( n & 1 ) { printf("0\n"); continue ; }
            printf("2 ");
            REP(i, 0, n - 1) if ( i % 2 == 0 ) printf("%d ", n - i); else printf("%d ", i); 
            puts("");
        }
        return 0;
    }
    return 0;
}

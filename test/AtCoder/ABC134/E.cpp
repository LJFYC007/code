/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时32分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], len, n, c[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &c[i]);
    a[0] = 2147483647;
    REP(i, 1, n)
    {
        if ( a[len] >= c[i] ) { a[++ len] = c[i]; continue ; }
        int L = 1, R = len, x = -1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( a[Mid] < c[i] ) { x = Mid; R = Mid - 1; }
            else L = Mid + 1;
        }
        a[x] = c[i];
    }
    printf("%d\n", len);
    return 0;
}

/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月08日 星期六 08时27分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 3;

LL a[5][maxn][maxn], n, m;

inline void cheng(int x, int y)
{
    REP(i, 1, 2) REP(j, 1, 2) 
    {
        a[3][i][j] = 0;
        REP(k, 1, 2) a[3][i][j] += (a[x][i][k] * a[y][k][j]) % m;
        a[3][i][j] %= m;
    }
    REP(i, 1, 2) REP(j, 1, 2) a[x][i][j] = a[3][i][j] % m;
}

inline void js(int b)
{
    while ( b ) 
    {
        if ( b & 1 ) cheng(2, 1);
        cheng(1, 1); b >>= 1;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    m = 10000;
    while ( 1 )
    {
        scanf("%lld", &n);
        if ( n == -1 ) break ; 
        if ( n == 0 || n == 1 || n == 2 ) { printf("%d\n", n == 0 ? 0 : 1); continue ; }
        a[1][1][1] = 1; a[1][1][2] = 1; a[1][2][1] = 1; a[1][2][2] = 0;
        REP(i, 1, 2) REP(j, 1, 2) a[2][i][j] = a[1][i][j]; 
        js(n - 2);
        printf("%lld\n", a[2][1][1] % m);
    }
    return 0;
}

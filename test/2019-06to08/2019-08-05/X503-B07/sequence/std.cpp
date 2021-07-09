/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年08月05日 星期一 09时05分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 3000010;

int n, sum1, sum2, sum3, sum4, ans[maxn], p[5][maxn];

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("sequence1.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int x, y; read(x); read(y);
        // a[i].x = x; a[i].y = y;
        if ( x == 0 && y == 0 ) p[1][++ sum1] = i;
        if ( x == 1 && y == 0 ) p[2][++ sum2] = i;
        if ( x == 0 && y == 1 ) p[3][++ sum3] = i;
        if ( x == 1 && y == 1 ) p[4][++ sum4] = i;
    }
    int x = n / 2;
    int L = 0, R = x;
    if ( sum2 > x ) { REP(i, x + 1, sum2) ans[++ R] = p[2][i]; sum2 = x; }
    if ( sum3 > x ) { REP(i, x + 1, sum3) ans[++ L] = p[3][i]; sum3 = x; }
    REP(i, 1, sum2) ans[++ L] = p[2][i];
    REP(i, 1, sum3) ans[++ R] = p[3][i];
    if ( sum2 < sum3 ) 
    {
        while ( sum2 < sum3 && sum3 > 0 ) { ans[++ L] = ans[R --]; -- sum3; }
        if ( L > x ) { puts("-1"); return 0; }
    }
    if ( sum2 > sum3 ) 
    {
        while ( sum2 > sum3 && sum2 > 0 ) { ans[++ R] = ans[L --]; -- sum2; }
        if ( R > n ) { puts("-1"); return 0; }
    }
    if ( sum2 == sum3 ) 
    {
        while ( sum4 > 0 && L <= x ) { ans[++ L] = ans[R]; ans[R] = p[4][sum4 --]; }
        if ( sum4 > 0 ) { puts("-1"); return 0; }
        // REP(i, 1, n) cerr << ans[i] << " ";
        REP(i, 1, n) if ( !ans[i] ) ans[i] = p[1][sum1 --];
        REP(i, 1, n) printf("%d ", ans[i]); puts(""); return 0;
    }
    return 0;
}

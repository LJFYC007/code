/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年06月08日 星期六 09时08分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5;

LL a[maxn][maxn][maxn], n, m;

inline void cheng(int x, int y)
{
    REP(i, 1, 3) REP(j, 1, 3)
    {
        a[3][i][j] = 0;
        REP(k, 1, 3) a[3][i][j] += (a[x][i][k] * a[y][k][j]) % m;
        a[3][i][j] %= m;
    }
    REP(i, 1, 3) REP(j, 1, 3) a[x][i][j] = a[3][i][j];
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
    scanf("%d%d", &n, &m);
    a[1][1][1] = a[1][1][2] = a[1][2][2] = a[1][2][3] = a[1][3][2] = 1;
    REP(i, 1, 3) REP(j, 1, 3) a[2][i][j] = a[1][i][j];
    js(n - 2);
    LL ans = 0; REP(i, 1, 3) ans += a[2][1][i];
    printf("%lld\n", ans % m);
    return 0;
}

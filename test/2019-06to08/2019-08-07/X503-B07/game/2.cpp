/***************************************************************
	File name: 2.cpp
	Author: ljfcnyali
	Create time: 2019年08月07日 星期三 09时19分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5010;

int f[maxn][maxn], n, m;

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n + m) f[0][i] = 1;
    f[1][1] = 2;
    REP(i, 2, n) f[i][1] = f[i - 1][1] * 2;
    // . . . . . .
    // . . . . .
    // . . . .
    REP(i, 1, n) REP(j, 2, m + n - i) 
    {
        f[i][j] = f[i][j - 1] + f[i - 1][j + 1];
        if ( i - 1 == j + 1 ) ++ f[i][j];
    }
    REP(i, 1, n) REP(j, 1, m) printf("%d %d %d\n", i, j, f[i][j]);
    printf("%d\n", f[n][m]);
    return 0;
}

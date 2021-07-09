/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2019年08月07日 星期三 08时50分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 15;

int a[maxn][maxn], n, m, ans;

inline void DFS(int x, int y)
{
    if ( x == n + 1 ) { REP(i, 1, n) { REP(j, 1, m) printf("%d ", a[i][j]); puts(""); } puts("");  ++ ans; return ; }
    if ( y == m + 1 ) { DFS(x + 1, 1); return ; }
    REP(i, a[x][y - 1] + 1, min(m, a[x - 1][y + 1] - 1)) { a[x][y] = i; DFS(x, y + 1); }
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) a[i][0] = -1, a[i][m + 1] = m + 1;
    REP(j, 1, m + 1) a[0][j] = m + 1;
    DFS(1, 1);
    printf("%d\n", ans);
    return 0;
}

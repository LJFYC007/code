/***************************************************************
	File name: P1896.cpp
	Author: ljfcnyali
	Create time: 2019年06月12日 星期三 14时56分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 20;

bool hack[maxn][maxn];
int n, k, dt[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
LL ans;

inline void DFS(int x, int y, int sum)
{
    if ( sum == k ) { ++ ans; return ; }
    if ( x == n + 1 ) return ; 
    if ( y == n + 1 ) { DFS(x + 1, 1, sum); return ; }
//    printf("%d %d %d\n", x, y, sum);
//    REP(i, 1, n) { REP(j, 1, n) printf("%d", hack[i][j]); puts(""); }
//    puts("");
    DFS(x, y + 1, sum);
    if ( hack[x][y] ) return ; 
    hack[x][y] = true;
    REP(i, 0, 7)
    {
        int u = dt[i][0] + x, v = dt[i][1] + y;
//        printf("%d %d %d %d %d\n", x, y, u, v, hack[u][v]);
        if ( hack[u][v] ) 
        {
            hack[x][y] = false;
//            REP(j, 0, i - 1)
//            {
//                int U = dt[j][0] + x, V = dt[j][1] + y;
//                hack[U][V] = false;
//            }
            return ;
        }
//        hack[u][v] = true;
    }
    DFS(x, y + 1, sum + 1);
    hack[x][y] = false;
    return ;
    REP(i, 0, 7)
    {
        int u = dt[i][0] + x, v = dt[i][1] + y;
        hack[u][v] = false;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    for ( n = 1; n <= 9; ++ n )
    {
        for ( k = 1; k <= n * n; ++ k )
        {
            if ( k != 1 && ans == 0 ) { printf("ans[%d][%d] = 0; ", n, k); continue ; }
            ans = 0; mem(hack);
            DFS(1, 1, 0);
            printf("ans[%d][%d] = %lld; ", n, k, ans);
            cerr << n << " " << k << endl;
        }
        puts("");
    }
    return 0;
}

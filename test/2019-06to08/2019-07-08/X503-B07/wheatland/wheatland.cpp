/***************************************************************
	File name: wheatland.cpp
	Author: ljfcnyali
	Create time: 2019年07月08日 星期一 08时01分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 210;

int n, m, k, a[maxn][maxn], dis[maxn][maxn][2 * maxn];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn][2 * maxn];

struct node
{
    int x, y, val, sum;
} p1, p2;

int main()
{
    freopen("wheatland.in", "r", stdin);
    freopen("wheatland.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n)
    {
        getchar();
        REP(j, 1, m)
        {
            char c = getchar();
            a[i][j] = c - '0';
        }
    }
    if ( n + m - 1 <= k ) { printf("%d\n", n + m - 2); return 0; }
    queue<node> Q; p1.x = p1.y = 1; p1.sum = 0; p1.val = a[1][1]; Q.push(p1);
    memset(dis, 0x3f, sizeof(dis));
    dis[1][1][a[1][1]] = 0;
    while ( !Q.empty() ) 
    {
        p1 = Q.front(); Q.pop();
//        cerr << p1.x << " " << p1.y << " " << p1.val << " " << p1.sum << endl;
        if ( p1.x == n && p1.y == m ) { printf("%d\n", p1.sum); return 0; }
        REP(i, 0, 3)
        {
            int u = p1.x + dt[i][0], v = p1.y + dt[i][1];
            if ( u < 1 || v < 1 || u > n || v > m ) continue ;
            if ( p1.val + a[u][v] > k ) continue ;
            p2.x = u; p2.y = v; p2.val = p1.val + a[u][v]; p2.sum = p1.sum + 1;
            if ( dis[p2.x][p2.y][p2.val] > p2.sum ) 
            {
                dis[p2.x][p2.y][p2.val] = p2.sum;
                if ( !vis[p2.x][p2.y][p2.val] ) 
                {
                    vis[p2.x][p2.y][p2.val] = true;
                    Q.push(p2);
                }
            }
        }
        vis[p1.x][p1.y][p1.val] = false;
    }
    int ans = 0x3f3f3f3f;
    REP(i, 0, k) ans = min(ans, dis[n][m][i]);
    if ( ans == 0x3f3f3f3f ) printf("no solution\n");
    else printf("%d\n", ans);
    return 0;
}

/***************************************************************
	File name: route.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 21时26分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, m, q, f[maxn][maxn], dis[maxn][maxn];

int main()
{
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
    cin >> n >> m >> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); f[u][v] = f[v][u] = min(f[u][v], w); }
    REP(i, 1, q)
    {
        int op, x, y;
        scanf("%d%d", &op, &x);
        if ( op == 1 ) 
        {
            if ( f[x][x] != 0x3f3f3f3f ) continue ;
            f[x][x] = 0; dis[x][x] = 0;
            REP(j, 1, n) dis[x][j] = dis[j][x] = f[x][j];
            // REP(j, 1, n) if ( f[j][j] == 0 ) dis[x][j] = dis[j][x] = f[x][j];
            REP(j, 1, n) REP(k, 1, n) dis[j][k] = min(dis[j][k], dis[j][x] + dis[x][k]);
        }
        else
        {
            scanf("%d", &y);
            printf("%d\n", dis[x][y] == 0x3f3f3f3f ? -1 : dis[x][y]);
        }
    }
    return 0;
}

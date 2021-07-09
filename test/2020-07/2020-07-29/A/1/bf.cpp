/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月29日 星期三 08时24分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;
const int INF = 1e7;

int n, m, a[maxn], dis[maxn][maxn], f[maxn][maxn];
bool vis[maxn][maxn];
struct node 
{ 
    int x, y; 
    node ( int a = 0, int b = 0 ) { x = a; y = b; } 
    bool operator < (const node &a) const { return f[x][y] > f[a.x][a.y]; } 
};
priority_queue<node> Q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = dis[i][j] = INF;
    REP(i, 1, n) { scanf("%d", &a[i]); dis[i][i] = a[i]; }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); dis[u][v] = a[u] + a[v]; }
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j] - a[k]);

    REP(i, 2, n) { f[1][i] = dis[i][1]; vis[1][i] = true; Q.push(node(1, i)); }
    while ( !Q.empty() ) 
    {
        node u = Q.top(); Q.pop();
        int i = u.x, j = u.y;
        REP(k, 2, n) REP(u, 2, n)
        {
            if ( k == i || k == j ) continue ;
            int ret = f[i][j] + dis[i][u] + dis[u][j] + dis[k][u];
            ret -= a[i] + a[j] + a[u] + a[u];
            if ( ret < f[j][k] ) { f[j][k] = ret; if ( !vis[j][k] ) { vis[j][k] = true; Q.push(node(j, k)); } }
        }
        vis[i][j] = false;
    }
    int ans = INF;
    REP(i, 1, n) ans = min(ans, f[i][n] + dis[i][n] - a[i] - a[n]);
    printf("%d\n", ans >= INF / 2 ? -1 : ans);
    return 0;
}


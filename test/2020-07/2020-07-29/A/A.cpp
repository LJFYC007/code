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

int n, m, a[maxn], dis[maxn][maxn], f[maxn][maxn], g[maxn][maxn], ans = INF;
bool vis[maxn][maxn];
struct node 
{ 
    int x, y, val, op; 
    node ( int a = 0, int b = 0, int c = 0, int d = 0 ) { x = a; y = b; val = c; op = d; } 
    bool operator < (const node &t) const { return val > t.val; }
    // bool operator < (const node &t) const { return val < t.val || (val == t.val && (x < t.x || (x == t.x && ((y < t.y || (y == t.y && op < t.op)))))); } 
};
priority_queue<node> Q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = dis[i][j] = g[i][j] = INF;
    REP(i, 1, n) { scanf("%d", &a[i]); dis[i][i] = a[i]; }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); dis[u][v] = a[u] + a[v]; }
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j] - a[k]);

    REP(i, 2, n) { f[1][i] = dis[i][1]; vis[1][i] = true; Q.push(node(1, i, f[1][i], 0)); }
    while ( !Q.empty() ) 
    {
        node u = Q.top(); Q.pop();
        int i = u.x, j = u.y, t = u.op;
        if ( t == 0 && f[i][j] < u.val ) continue ;
        if ( t == 1 && g[i][j] < u.val ) continue ;
        if ( j == n && !t ) { ans = min(ans, f[i][n] + dis[i][n] - a[i] - a[n]); continue ; }
        if ( t == 1 ) REP(k, 2, n) 
        {
            if ( k == j ) continue ; 
            int ret = u.val + dis[i][j] + dis[k][i];
            ret -= a[i] + a[j] + a[i];
            if ( ret < f[j][k] ) 
            { 
                f[j][k] = ret; 
                Q.push(node(j, k, ret, 0));
            }
        }
        else REP(k, 1, n)
        {
            int ret = u.val + dis[i][k] - a[i];
            if ( ret < g[k][j] ) 
            {
                g[k][j] = ret;
                Q.push(node(k, j, g[k][j], 1));
            }
        }
    }
    printf("%d\n", ans >= INF / 2 ? -1 : ans);
    return 0;
}

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

int n, m, a[maxn], dis[maxn][maxn], f[maxn][maxn], ans = INF;
bool vis[maxn][maxn];
struct node 
{ 
    int x, y, val; 
    node ( int a = 0, int b = 0, int c = 0 ) { x = a; y = b; val = c; } 
    bool operator < (const node &t) const { return val < t.val || (val == t.val && (x < t.x || (x == t.x && y < t.y))); } 
};
set<node> Set;

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

    REP(i, 2, n) { f[1][i] = dis[i][1]; vis[1][i] = true; Set.insert(node(1, i, f[1][i])); }
    while ( !Set.empty() ) 
    {
        node u = *Set.begin(); Set.erase(Set.begin()); 
        int i = u.x, j = u.y;
        if ( u.val >= ans ) break ; 
        if ( j == n ) { ans = min(ans, f[i][n] + dis[i][n] - a[i] - a[n]); continue ; }
        REP(k, 2, n) 
        {
            if ( k == i || k == j ) continue ;
            REP(u, 2, n)
            {
                int ret = f[i][j] + dis[i][u] + dis[u][j] + dis[k][u];
                ret -= a[i] + a[j] + a[u] + a[u];
                if ( ret < f[j][k] ) 
                { 
                    Set.erase(node(j, k, f[j][k]));
                    f[j][k] = ret; 
                    Set.insert(node(j, k, ret));
                }
            }
        }
    }
    printf("%d\n", ans >= INF / 2 ? -1 : ans);
    return 0;
}

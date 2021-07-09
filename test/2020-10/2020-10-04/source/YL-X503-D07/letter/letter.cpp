/***************************************************************
	File name: letter.cpp
	Author: ljfcnyali
	Create time: 2020年10月04日 星期日 09时18分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn];
int anc[maxn][20];
pii a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

int main()
{
    freopen("letter.in", "r", stdin);
    freopen("letter.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m) { scanf("%d%d", &a[i].x, &a[i].y); if ( dis[a[i].x] < dis[a[i].y] ) swap(a[i].x, a[i].y); }
    while ( q -- ) 
    {
        int t, x, y; scanf("%d%d%d", &t, &x, &y);
        if ( dis[x] < dis[y] ) swap(x, y);
        if ( t == 2 ) { a[++ m] = pii(x, y); continue ; }
        t = LCA(x, y);
        int ans = 0;
        REP(i, 1, m)
        {
            int pos = LCA(a[i].x, a[i].y);
            if ( pos == a[i].y ) 
            {
                if ( LCA(x, a[i].x) == a[i].x && LCA(a[i].y, t) == t ) ++ ans;
                if ( LCA(y, a[i].x) == a[i].x && LCA(a[i].y, t) == t ) ++ ans;
            }
            else if ( pos == t ) 
            {
                if ( LCA(x, a[i].x) == a[i].x && LCA(y, a[i].y) == a[i].y ) ++ ans;
                if ( LCA(y, a[i].x) == a[i].x && LCA(x, a[i].y) == a[i].y ) ++ ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

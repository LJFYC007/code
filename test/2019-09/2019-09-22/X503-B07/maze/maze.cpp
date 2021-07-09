/***************************************************************
	File name: maze.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 10时18分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e;
int dis[20010], n, m, q, dt[3][2] = {{1, 0}, {-1, 0}, {0, 1}}, a[10][50010];
bool vis[20010];

inline int Place(int x, int y) { return (x - 1) * m + y; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int read()
{
    int x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) x = x * 10 + c - '0', c = getchar();
    return x;
}

signed main()
{
    freopen("maze.in", "r", stdin);
    freopen("maze.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) REP(j, 1, m) REP(k, 0, 2)
    {
        int u = i + dt[k][0], v = j + dt[k][1];
        if ( u < 1 || u > n || v < 1 || v > m ) continue ;
        add(Place(i, j), Place(u, v));
    }
    REP(i, 1, n) REP(j, 1, m) a[i][j] = read();
    while ( q -- ) 
    {
        int opt = read(), x = read(), y = read();
        if ( opt == 1 ) { a[x][y] ^= 1; continue ; }
        if ( a[x][y] == 0 ) { puts("-1"); continue ; }
        int s = Place(x, y), t;
        x = read(); y = read(); t = Place(x, y);
        if ( a[x][y] == 0 ) { puts("-1"); continue ; }
        queue<int> Q; Q.push(s);
        REP(i, 0, 20000) { dis[i] = INF; vis[i] = false ; }
        dis[s] = 0;
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            int p1 = u / m + 1, p2 = u % m;
            if ( p2 > y || !a[p1][p2] ) continue ;
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i]; 
                if ( dis[v] > dis[u] + 1 ) 
                {
                    dis[v] = dis[u] + 1;
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        printf("%d\n", dis[t] == INF ? -1 : dis[t]);
    }
    return 0;
}

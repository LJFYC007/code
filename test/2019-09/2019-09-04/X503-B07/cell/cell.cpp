/***************************************************************
	File name: cell.cpp
	Author: ljfcnyali
	Create time: 2019年09月05日 星期四 20时38分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, a[1010][1010], s, t, dis[maxn], Min[1010][1010];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn];

struct node
{
    int x, y;
} p1, p2;

inline int Place(int x, int y) { return (x - 1) * m + y; }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline char get()
{
    char c = getchar();
    while ( c == ' ' || c == '\n' || c == '\r' ) c = getchar();
    return c;
}

queue<node> Q1;

inline void BFS()
{
    while ( !Q1.empty() ) 
    {
        p1 = Q1.front(); Q1.pop();
        REP(i, 0, 3)
        {
            p2.x = p1.x + dt[i][0]; p2.y = p1.y + dt[i][1];
            if ( !a[p2.x][p2.y] || Min[p2.x][p2.y] ) continue ;
            Min[p2.x][p2.y] = Min[p1.x][p1.y] + 1;
            Q1.push(p2);
        }
    }
}

int main()
{
    freopen("cell.in", "r", stdin);
    freopen("cell.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    {
        REP(j, 1, m)
        {
            char c = get();
            if ( c == 'C' ) s = Place(i, j);
            if ( c == 'F' ) t = Place(i, j);
            if ( c != '#' ) a[i][j] = 1;
            else { p1.x = i; p1.y = j; Q1.push(p1); }
        }
    }
    BFS();
    // REP(i, 1, n) { REP(j, 1, m) printf("%d ", Min[i][j]); puts(""); }
    REP(i, 1, n) REP(j, 1, m) 
    {
        if ( !a[i][j] ) continue ;
        REP(k, 0, 3)
        {
            int u = i + dt[k][0], v = j + dt[k][1];
            if ( !a[u][v] ) continue ;
            add(Place(i, j), Place(u, v), 1);
        }
        REP(k, 0, 3)
        {
            int u = i, v = j;
            while ( a[u + dt[k][0]][v + dt[k][1]] ) { u += dt[k][0]; v += dt[k][1]; }
            add(Place(i, j), Place(u, v), Min[i][j]);
        }
    }
    memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    queue<int> Q; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        if ( u == t ) continue ;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    if ( dis[t] == 0x3f3f3f3f ) puts("no");
    else printf("%d\n", dis[t]);
    return 0;
}

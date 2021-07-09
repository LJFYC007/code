/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 20时14分12秒
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

const int maxn = 1e4 + 10;
const int INF = 2e9;

int n, m, a[maxn], g, r, dis[maxn][1010], ans = INF;
bool vis[maxn][1010];
struct node 
{
    int x, y, t;
    node ( int a = 0, int b = 0, int c = 0) { x = a; y = b; t = c; }
    bool operator < (const node &a) const { return t > a.t; }
} ;
priority_queue<node> Q;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d", &a[i]);
    sort(a + 1, a + m + 1);
    scanf("%d%d", &g, &r);
    REP(i, 1, m) REP(j, 0, g) dis[i][j] = INF;
    dis[1][0] = 0; Q.push(node(1, 0, 0));
    while ( !Q.empty() ) 
    {
        node t = Q.top(); Q.pop();
        int x = t.x, y = t.y;
        if ( vis[x][y] ) continue ; vis[x][y] = true;
        if ( x == m ) { printf("%d\n", dis[x][y]); return 0; }
        if ( t.second == g ) 
        {
            if ( dis[t.first][0] > dis[t.first][t.second] + r )
            {
                dis[t.first][0] = dis[t.first][t.second] + r;
                Q.push(node(x, 0, dis[x][y] + r));
            }
        }
        if ( t.first < m )
        {
            int s = a[x + 1] - a[x];
            if ( s + y <= g && dis[x + 1][y + s] > dis[x][y] + s )
            {
                dis[x + 1][y + s] = dis[x][y] + s;
                Q.push(node(x + 1, y + s, dis[x][y] + s));
            }
        }
        if ( t.first > 1 ) 
        {
            int s = a[x] - a[x - 1];
            if ( s + y <= g && dis[x - 1][y + s] > dis[x][y] + s )
            {
                dis[x - 1][y + s] = dis[x][y] + s;
                Q.push(node(x - 1, y + s, dis[x][y] + s));
            }
        }
    }
    puts("-1");
    return 0;
}

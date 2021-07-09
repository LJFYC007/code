/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 17时26分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5000010;

int n, m, sum, ans = 2, dt[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
char a[maxn];
bool vis[maxn], ok[maxn];

struct node
{
    int x, y;
} p1, p2;

inline int Place(int x, int y) 
{ 
    if ( x < 1 || y < 1 || x > n || y > m ) return 0;
    return (x - 1) * m + y; 
}

inline void BFS()
{
    queue<node> Q; p1.x = n; p1.y = m; Q.push(p1);
    vis[Place(n, m)] = true;
    while ( !Q.empty() ) 
    {
        p1 = Q.front(); Q.pop();
        REP(k, 2, 3)
        {
            int u = p1.x + dt[k][0], v = p1.y + dt[k][1];
            if ( u < 1 || v < 1 || u > n || v > m ) continue ;
            if ( !vis[Place(u, v)] && a[Place(u, v)] == '.' ) { vis[Place(u, v)] = true; p2.x = u; p2.y = v; Q.push(p2); }
        }
    }
    if ( !vis[Place(1, 1)] ) { puts("0"); exit(0); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { getchar(); REP(j, 1, m) scanf("%c", &a[Place(i, j)]); }
    BFS();
    queue<node> Q;
    p1.x = p1.y = 1; Q.push(p1);
    while ( !Q.empty() ) 
    {
        p1 = Q.front(); Q.pop(); -- sum;
        REP(k, 0, 1)
        {
            int u = p1.x + dt[k][0], v = p1.y + dt[k][1];
            if ( u < 1 || v < 1 || u > n || v > m ) continue ;
            if ( a[Place(u, v)] == '#' || !vis[Place(u, v)] || ok[Place(u, v)] ) continue ;
            ok[Place(u, v)] = true;
            p2.x = u; p2.y = v; Q.push(p2);
        }
        if ( ok[Place(n, m)] ) break ; 
        ans = min(ans, (int)Q.size());
    }
    printf("%d\n", ans);
    return 0;
}

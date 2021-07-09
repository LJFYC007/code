/***************************************************************
	File name: P3959.cpp
	Author: ljfcnyali
	Create time: 2019年07月03日 星期三 08时54分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20;

int f[maxn][maxn], n, m, dis[maxn], ans = 0x3f3f3f3f, tot, sum;
bool vis[maxn];

struct node
{
    int u, v;
    bool operator < (const node &a) const
    {
        return dis[u] * f[u][v] > dis[a.u] * f[a.u][a.v];
    }
} p1, p2;

inline void Solve(int s)
{
    mem(dis); mem(vis); tot = sum = 0;
    priority_queue<node> Q;
    node a[1010];     
    dis[s] = 1; vis[s] = true;
    REP(i, 1, n) if ( i != s && f[s][i] != 0x3f3f3f3f ) { p1.u = s; p1.v = i; Q.push(p1); } 
    REP(i, 2, n)
    {
        p1 = Q.top(); Q.pop();
        while ( !Q.empty() && (vis[p1.v] || !(rand() % n)) )
        {
            if ( !vis[p1.v] ) a[++ tot] = p1; 
            p1 = Q.top(); Q.pop();
        }
        vis[p1.v] = true; dis[p1.v] = dis[p1.u] + 1;
        REP(i, 1, tot) Q.push(a[i]); tot = 0;
        REP(j, 1, n)
            if ( f[p1.v][j] != 0x3f3f3f3f && !vis[j] ) 
            {
                p2.u = p1.v;
                p2.v = j;
                Q.push(p2);
            }
        sum += dis[p1.u] * f[p1.u][p1.v];
        if ( sum >= ans ) return ;
    }
    ans = min(ans, sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        f[u][v] = f[v][u] = min(f[u][v], w);
    }
    REP(i, 1, 3000) 
        REP(i, 1, n) Solve(i);
    printf("%d\n", ans);
    return 0;
}

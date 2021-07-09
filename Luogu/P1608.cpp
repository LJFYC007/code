/***************************************************************
    File name: P1608.cpp
    Author: ljfcnyali
    Create time: 2019年06月16日 星期日 09时48分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int n, m, f[maxn][maxn];
int dis[maxn], ans[maxn];
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); f[u][v] = min(f[u][v], w); }
    REP(i, 2, n) dis[i] = 0x3f3f3f3f;
    queue<int> Q; Q.push(1);
    ans[1] = 1; vis[1] = true;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); 
        if ( u == n ) continue ;
        REP(v, 1, n)
        {
            if ( f[u][v] == 0x3f3f3f3f || u == v ) continue ;
            if ( dis[v] >= dis[u] + f[u][v] ) 
            {
                if ( dis[v] > dis[u] + f[u][v] ) { dis[v] = dis[u] + f[u][v]; ans[v] = 0; }
                ans[v] += ans[u];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
        vis[u] = false;
        ans[u] = 0;
    }
    if ( dis[n] != 0x3f3f3f3f ) printf("%d %d\n", dis[n], ans[n]);
    else printf("No answer\n");
    return 0;
}

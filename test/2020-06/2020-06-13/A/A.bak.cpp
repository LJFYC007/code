/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2020年06月13日 星期六 09时09分01秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 410;
const unsigned int INF = 1e9;
 
int q, n, m, k, p1[maxn], p2[maxn];
unsigned int f[410][410], sum[410][410], ans[410][410], dis[33][33][1 << 16];
bool Vis[maxn];
vector<pii> Q[maxn];
vector<int> key1, key2;
struct node 
{ 
    int u, s; unsigned int d; 
    node ( int x = 0, int y = 0, unsigned int z = 0 ) { u = x; s = y; d = z; }
    bool operator < (const node &a) const { return d > a.d; }
} ;
priority_queue<node> Queue;
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = INF;
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m) { int u, v; unsigned int w; scanf("%d%d%u", &u, &v, &w); f[u][v] = f[v][u] = min(f[u][v], w); }
 
    REP(i, 0, k - 1) 
    { 
        int x, y; scanf("%d%d", &x, &y); 
        p1[x] |= (1 << i); p2[y] |= (1 << i); 
        key1.push_back(x); key2.push_back(y);
        Vis[x] = true;
    }
    REP(o, 1, n) 
    {
        if ( Vis[o] ) continue ;
        REP(i, 1, n) REP(j, 1, n) f[i][j] = f[j][i] = min(f[i][j], f[i][o] + f[o][j]);
    }
 
    REP(i, 0, 31) REP(j, 0, 31) 
    {
        REP(o, 0, (1 << k) - 1) dis[i][j][o] = INF;
        sum[i][j] = INF;
    }
 
    int num = key2.size();
    REP(S, 0, num - 1)
    {
        Queue.push(node(S, p2[key2[S]])); 
        sum[S][S] = dis[S][S][p2[key2[S]]] = 0;
        while ( !Queue.empty() ) 
        {
            node x = Queue.top(); Queue.pop();
            if ( x.d > dis[S][x.u][x.s] ) continue ;
            int t = x.u >= num ? key1[x.u - num] : key2[x.u];
 
            for ( int i = 0; i < key1.size(); ++ i ) 
            {
                node v = node(num + i, x.s);
                if ( (v.s & p1[key1[i]]) != p1[key1[i]] ) continue ;
                v.s |= p2[key1[i]];
                if ( dis[S][v.u][v.s] > dis[S][x.u][x.s] + f[t][key1[i]] )
                {
                    dis[S][v.u][v.s] = dis[S][x.u][x.s] + f[t][key1[i]];
                    sum[S][v.u] = min(sum[S][v.u], dis[S][v.u][v.s]);
                    v.d = dis[S][v.u][v.s]; Queue.push(v);
                }
            }
 
            for ( int i = 0; i < key2.size(); ++ i ) 
            {
                node v = node(i, x.s);
                if ( (v.s & p1[key2[i]]) != p1[key2[i]] ) continue ;
                v.s |= p2[key2[i]];
                if ( dis[S][v.u][v.s] > dis[S][x.u][x.s] + f[t][key2[i]] )
                {
                    dis[S][v.u][v.s] = dis[S][x.u][x.s] + f[t][key2[i]];
                    sum[S][v.u] = min(sum[S][v.u], dis[S][v.u][v.s]);
                    v.d = dis[S][v.u][v.s]; Queue.push(v);
                }
            }
        }
    }
 
    REP(u, 1, n) REP(v, 1, n)
    {
        ans[u][v] = INF;
        if ( p1[u] ) continue ;
        if ( !p1[u] && !p1[v] ) ans[u][v] = min(ans[u][v], f[u][v]);
        REP(i, 0, num - 1)
        {
            if ( p1[key2[i]] ) continue ;
            if ( !p1[v] ) REP(j, 0, num - 1) ans[u][v] = min(ans[u][v], f[u][key2[i]] + sum[i][j] + f[key2[j]][v]);
            for ( int j = 0; j < key1.size(); ++ j ) 
                if ( !p1[v] || v == key1[j] ) 
                    ans[u][v] = min(ans[u][v], f[u][key2[i]] + sum[i][num + j] + f[key1[j]][v]);
        }
    }
    scanf("%d", &q);
    REP(i, 1, q)
    {
        int u, v; scanf("%d%d", &u, &v);
        printf("%d\n", ans[u][v] >= INF ? -1 : ans[u][v]);
    }
    return 0;
}

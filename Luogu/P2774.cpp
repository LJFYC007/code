/***************************************************************
	File name: P2774.cpp
	Author: ljfcnyali
	Create time: 2019年07月19日 星期五 20时30分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010 * 2;
const int maxm = 210;
const int INF = 0x3f3f3f3f;

int n, m, s, t, a[maxm][maxm], ans, tot = 0;
int dt[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e = 1, dis[maxn];

    inline void add(int u, int v, int w)
    {
        To[++ e] = v;
        Next[e] = Begin[u];
        Begin[u] = e;
        W[e] = w;
    }

    inline bool BFS(int s, int t)
    {
        queue<int> Q; Q.push(s);
        mem(dis); dis[s] = 1;
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] )
            {
                int v = To[i]; if ( dis[v] || !W[i] ) continue ;
                dis[v] = dis[u] + 1;
                if ( v == t ) return true;
                Q.push(v);
            }
        }
        return false;
    }

    inline int DFS(int u, int t, int flow)
    {
        if ( u == t || !flow ) return flow;
        int f = 0;
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ;
            int x = DFS(v, t, min(flow, W[i]));
            if ( !x ) continue ;
            flow -= x; f += x;
            W[i] -= x; W[i ^ 1] += x;
        }
        if ( !f ) dis[u] = 0;
        return f;
    }

    inline int Solve(int s, int t)
    {
        int Maxflow = 0;
        while ( BFS(s, t) )
            while ( int flow = DFS(s, t, INF) )
                Maxflow += flow;
        return Maxflow;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    t = n * m + 1;
    REP(i, 1, n) REP(j, 1, m) 
    { 
        scanf("%d", &a[i][j]); ans += a[i][j]; 
        ++ tot;
        if ( (i + j) % 2 == 0 ) { Dinic :: add(s, tot, a[i][j]); Dinic :: add(tot, s, 0); }
        else { Dinic :: add(tot, t, a[i][j]); Dinic :: add(t, tot, 0); }
    }
    REP(i, 1, n) REP(j, 1, m)
    {
        if ( (i + j) % 2 == 1 ) continue ;
        REP(k, 0, 3)
        {
            int u = dt[k][0] + i, v = dt[k][1] + j;
            if ( u < 1 || v < 1 || u > n || v > m ) continue ;
            Dinic :: add((u - 1) * m + v, (i - 1) * m + j, 0);
            Dinic :: add((i - 1) * m + j, (u - 1) * m + v, INF);
        }
    }
    ans -= Dinic :: Solve(s, t);
    printf("%d\n", ans);
    return 0;
}

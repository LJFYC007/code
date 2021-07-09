/***************************************************************
	File name: flow.cpp
	Author: ljfcnyali
	Create time: 2019年08月10日 星期六 10时42分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 410;
const int INF = 0x3f3f3f3f;	

int n, m, D, Edge[maxn][2], ans, d[maxn];

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e = 1, dis[maxn];

    inline void add(int u, int v, int w)
    {
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
        To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0;
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
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &D);
    int s = 0, t = n + n + 1;
    REP(i, 1, m) { scanf("%d%d", &Edge[i][0], &Edge[i][1]); ++ d[Edge[i][0]]; ++ d[Edge[i][1]]; }
    REP(i, 1, n) { Dinic :: add(i, i + n, INF); Dinic :: add(s, i, d[i]); Dinic :: add(i + n, t, INF); }
    REP(i, 1, m) { Dinic :: add(Edge[i][0] + n, Edge[i][1], INF); Dinic :: add(Edge[i][1] + n, Edge[i][0], INF); }
    printf("%d\n", Dinic :: Solve(s, t));
    return 0;
}

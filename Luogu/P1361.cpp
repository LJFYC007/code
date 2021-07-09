/***************************************************************
	File name: P1361.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 15时51分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;
const int INF = 0x3f3f3f3f;	

int n, m, s, t = 4010, tot, ans;

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
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int x; scanf("%d", &x); Dinic :: add(s, i, x); ans += x; }
    REP(i, 1, n) { int x; scanf("%d", &x); Dinic :: add(i, t, x); ans += x; }
    scanf("%d", &m);
    tot = 2 * n;
    REP(i, 1, m)
    {
        int k, c1, c2; scanf("%d%d%d", &k, &c1, &c2);
        Dinic :: add(s, tot + 1, c1); Dinic :: add(tot + 2, t, c2);
        REP(j, 1, k) { int x; scanf("%d", &x); Dinic :: add(tot + 1, x, INF); Dinic :: add(x, tot + 2, INF); }
        tot += 2;
        ans += c1 + c2;
    }
    printf("%d\n", ans - Dinic :: Solve(s, t));
    return 0;
}

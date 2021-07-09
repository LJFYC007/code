/***************************************************************
	File name: P2765.cpp
	Author: ljfcnyali
	Create time: 2019年07月19日 星期五 15时55分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;
const int INF = 1 << 30;

int n, m, s, t = 10000, nxt[maxn], w[maxn];
bool vis[maxn];

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
                // if ( v == t ) return true;
                Q.push(v);
            }
        }
        if ( dis[t] ) return true;
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
            if ( x > 0 ) nxt[u >> 1] = To[i] >> 1;
            flow -= x; f += x;
            W[i] -= x; W[i ^ 1] += x;
        }
        if ( !f ) dis[u] = -1;
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
    int now = 0, sum = 0;
    while ( sum <= n ) 
    {
        ++ now;
        Dinic :: add(s, now << 1, 1); 
        Dinic :: add(now << 1, s, 0); 
        Dinic :: add(now << 1 | 1, t, 1);
        Dinic :: add(t, now << 1 | 1, 0);
        for ( int i = sqrt(now) + 1; i * i < now * 2; ++ i )
        {
            Dinic :: add((i * i - now) << 1, now << 1 | 1, 1);
            Dinic :: add(now << 1 | 1, (i * i - now) << 1, 0);
        }
        if ( !Dinic :: Solve(s, t) ) w[++ sum] = now;
    }
    printf("%d\n", now - 1);
    REP(i, 1, n) 
    {
        if ( vis[w[i]] ) continue ;
        int k = w[i]; printf("%d ", k); vis[k] = true;
        while ( nxt[k] && nxt[k] != (t / 2) )
        {
            printf("%d ", nxt[k]); k = nxt[k]; vis[k] = true;
        }
        puts("");
    }
    // 忘记建反边了...
    return 0;
}

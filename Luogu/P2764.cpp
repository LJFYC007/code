/***************************************************************
	File name: P2764.cpp
	Author: ljfcnyali
	Create time: 2019年07月19日 星期五 19时35分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;
const int INF = 0x3f3f3f3f;

int n, m, s, t, ans;
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

    inline void DFS(int u)
    {
        if ( vis[u] ) return ;
        vis[u] = vis[u < n ? u + n : u - n] = true;
        printf("%d ", u);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( i % 2 == 0 && !W[i] && !vis[v] ) { DFS(v - n); return ; }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    t = 2 * n + 1;
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        Dinic :: add(u, n + v, 1); Dinic :: add(n + v, u, 0);
    }
    REP(i, 1, n) 
    { 
        Dinic :: add(s, i, 1); Dinic :: add(i, s, 0); 
        Dinic :: add(n + i, t, 1); Dinic :: add(t, n + i, 0); 
    }
    ans = Dinic :: Solve(s, t);
    vis[t] = true;
    REP(i, 1, n) if ( !vis[i] ) { Dinic :: DFS(i); puts(""); }
    printf("%d\n", n - ans);
    return 0;
}

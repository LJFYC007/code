/***************************************************************
	File name: P1231.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 19时42分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;	

int n1, n2, n3, m1, m2, s, t;

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
    scanf("%d%d%d", &n1, &n2, &n3); 
    t = n1 + n1 + n2 + n3 + 1;
    REP(i, 1, n1) Dinic :: add(i, i + n1, 1);
    REP(i, 1, n2) Dinic :: add(s, n1 + n1 + i, 1);
    REP(i, 1, n3) Dinic :: add(n1 + n1 + n2 + i, t, 1);
    scanf("%d", &m1); REP(i, 1, m1) { int x, y; scanf("%d%d", &x, &y); Dinic :: add(n1 + n1 + y, x, 1); }
    scanf("%d", &m2); REP(i, 1, m2) { int x, y; scanf("%d%d", &x, &y); Dinic :: add(x + n1, n1 + n1 + n2 + y, 1); }
    printf("%d\n", Dinic :: Solve(s, t));
    return 0;
}

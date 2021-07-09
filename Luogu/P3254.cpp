/***************************************************************
	File name: P3254.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 10时11分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;
const int INF = 0x3f3f3f3f;	

int n, m, s, t, sum;

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
    scanf("%d%d", &m, &n); t = m + n + 1;
    REP(i, 1, m) { int x; scanf("%d", &x); Dinic :: add(s, i, x); sum += x; }
    REP(i, 1, n) { int x; scanf("%d", &x); Dinic :: add(m + i, t, x); }
    REP(i, 1, m) REP(j, 1, n) Dinic :: add(i, m + j, 1); 
    if ( Dinic :: Solve(s, t) != sum ) { printf("0\n"); return 0; }
    puts("1");
    REP(u, 1, m)
    {
        for ( int i = Dinic :: Begin[u]; i; i = Dinic :: Next[i] ) 
        {
            int v = Dinic :: To[i]; if ( Dinic :: W[i] || v == s ) continue ;
            printf("%d ", v - m);
        }
        puts("");
    }
    return 0;
}

/***************************************************************
	File name: P2766.cpp
	Author: ljfcnyali
	Create time: 2019年07月21日 星期日 08时56分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxm = 10010;
const int maxn = 30000010;
const int INF = 0x3f3f3f3f;	

int n, s, t, dp[maxm], ans, a[maxm];

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e = 1, dis[maxn];

    inline void INIT()
    {
        e = 1; mem(Begin);
    }

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
    if ( n == 1 ) { printf("1\n1\n1\n"); return 0; }
    t = 2 * n + 1;
    REP(i, 1, n) { scanf("%d", &a[i]); dp[i] = 1; Dinic :: add(i, i + n, 1); }
    REP(i, 2, n) REP(j, 1, i - 1) if ( a[j] <= a[i] ) dp[i] = max(dp[i], dp[j] + 1);
    REP(i, 2, n) REP(j, 1, i - 1) if ( a[j] <= a[i] && dp[i] == dp[j] + 1 ) Dinic :: add(j + n, i, 1);
    REP(i, 1, n) ans = max(ans, dp[i]); printf("%d\n", ans);
    REP(i, 1, n) { if ( dp[i] == 1 ) Dinic :: add(s, i, 1); if ( dp[i] == ans ) Dinic :: add(i + n, t, 1); }
    int sum = ans; ans = Dinic :: Solve(s, t);
    printf("%d\n", ans);
    Dinic :: INIT();
    REP(i, 1, n) Dinic :: add(i, i + n, 1);
    REP(i, 2, n) REP(j, 1, i - 1) if ( a[j] <= a[i] && dp[i] == dp[j] + 1 ) Dinic :: add(j + n, i, 1);
    REP(i, 1, n) { if ( dp[i] == 1 ) Dinic :: add(s, i, 1); if ( dp[i] == sum ) Dinic :: add(i + n, t, 1); }
    Dinic :: add(s, 1, INF); Dinic :: add(1, n + 1, INF); 
    if ( dp[n] == sum ) { Dinic :: add(n, n + n, INF); Dinic :: add(n + n, t, INF); }
    ans = Dinic :: Solve(s, t);
    printf("%d\n", ans);
    return 0;
 }

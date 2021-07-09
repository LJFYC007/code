/***************************************************************
	File name: P2805.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 19时24分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 10000010;
const int INF = 10000000000000000;	

int n, m, s, t, a[300][300], ans;
bool use[maxn];

inline int Place(int x, int y) { return (x - 1) * m + y; }

namespace toposort
{
    int Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];

    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; }

    inline void Solve()
    {
        queue<int> Q;
        REP(i, 1, n * m) if ( !deg[i] ) Q.push(i);
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop(); use[u] = true;
            // printf("%d\n", u);
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i]; -- deg[v];
                if ( !deg[v] && !use[v] ) Q.push(v);
            }
        }
    }
}

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

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m); t = maxn - 1; s = maxn - 2;
    REP(i, 1, n) REP(j, 1, m) 
    {
        int sum; scanf("%lld%lld", &a[i][j], &sum);
        if ( j < m ) toposort :: add(Place(i, j + 1), Place(i, j));
        REP(k, 1, sum)
        {
            int x, y; scanf("%lld%lld", &x, &y); ++ x; ++ y;
            toposort :: add(Place(i, j), Place(x, y));
        }
    }
    toposort :: Solve();
    REP(i, 1, n) REP(j, 1, m)
    {
        int u = Place(i, j);
        // printf("UnPlcee :: %d %d %d\n", u, i, j);
        if ( !use[u] ) continue ;
        // printf("Plcee :: %d %d %d\n", u, i, j);
        if ( a[i][j] < 0 ) Dinic :: add(u, t, -a[i][j]);
        else { Dinic :: add(s, u, a[i][j]); ans += a[i][j]; }
        for ( int x = toposort :: Begin[u]; x; x = toposort :: Next[x] ) 
        {
            int v = toposort :: To[x]; if ( !use[v] ) continue ;
            Dinic :: add(v, u, INF);
        }
    }
    printf("%lld\n", ans - Dinic :: Solve(s, t));
    return 0;
}

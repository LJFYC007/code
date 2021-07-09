/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月09日 星期二 10时07分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int delta = 300;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], ans;

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

using namespace Dinic;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int s = n + n + 1, t = n + n + 2;
    REP(i, 1, n) 
    {
        scanf("%d", &a[i]);
        add(i, i + n, delta);
        add(s, i, a[i] + delta); add(i + n, t, a[i] + delta);
        ans += a[i] + delta; 
    }
    REP(i, 1, m) 
    { 
        int u, v; scanf("%d%d", &u, &v); 
        add(u, v, INF); add(u + n, v + n, INF); 
    }
    ans -= Solve(s, t);
    printf("%d\n", ans);
    return 0;
}

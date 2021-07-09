/***************************************************************
	File name: P4014.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 19时59分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;	

int n, flow, cost, s, t, a[110][110];

namespace MCMF 
{
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e = 1, W[maxn], F[maxn];
    int dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn];
    
    inline void INIT() { e = 1; mem(Begin); }

    inline void add(int u, int v, int w, int f) 
    { 
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
        To[++ e] = u; From[e] = v; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0; F[e] = -f; 
    }

    inline bool BFS(int s, int t)
    {
        memset(dis, 0x3f, sizeof(dis)); mem(vis);
        dis[s] = 0; a[s] = INF; vis[s] = true;
        queue<int> Q; Q.push(s);
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i];
                if ( dis[v] > dis[u] + F[i] && W[i] > 0 ) 
                {
                    dis[v] = dis[u] + F[i];
                    a[v] = min(a[u], W[i]);
                    pre[v] = i;
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        if ( dis[t] == INF ) return false;
        return true;
    }

    inline bool SPFA(int s, int t, int &flow, int &cost)
    {
        if ( !BFS(s, t) ) return false;
        flow += a[t]; cost += a[t] * dis[t];
        int u = t;
        while ( u != s ) 
        {
            W[pre[u]] -= a[t]; 
            W[pre[u] ^ 1] += a[t];
            u = From[pre[u]];
        }
        return true;
    }

    inline void Solve(int s, int t, int &flow, int &cost) 
    {
        flow = cost = 0;
        while ( SPFA(s, t, flow, cost) ) ;        
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    t = n + n + 1;
    REP(i, 1, n) 
    {
        // Dinic :: add(s, i, INF);
        // Dinic :: add(n + i, t, INF);
        MCMF :: add(s, i, 1, 0);
        MCMF :: add(n + i, t, 1, 0);
    }
    int Max = 0;
    REP(i, 1, n) REP(j, 1, n)
    {
        int x; scanf("%d", &x); a[i][j] = x; Max = max(Max, x);
        // Dinic :: add(i, n + j, x);
        MCMF :: add(i, n + j, 1, x);
    }
    MCMF :: Solve(s, t, flow, cost); 
    printf("%d\n", cost);
    MCMF :: INIT();
    REP(i, 1, n) 
    {
        MCMF :: add(s, i, 1, 0);
        MCMF :: add(n + i, t, 1, 0);
    }
    REP(i, 1, n) REP(j, 1, n)
    {
        int x = Max - a[i][j];
        // Dinic :: add(i, n + j, x);
        MCMF :: add(i, n + j, 1, x);
    }
    MCMF :: Solve(s, t, flow, cost); 
    printf("%d\n", Max * n - cost);
    return 0;
}

/***************************************************************
	File name: P2045.cpp
	Author: ljfcnyali
	Create time: 2019年08月12日 星期一 14时26分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, m, s, t, flow, cost;

namespace MCMF 
{
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e = 1, W[maxn], F[maxn];
    int dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn];

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
    scanf("%d%d", &n, &m);
    t = 2 * n * n + 1;
    MCMF :: add(s, 1, m, 0); MCMF :: add(2 * n * n, t, m, 0);
    int num = 0;
    REP(i, 1, n) REP(j, 1, n) 
    { 
        ++ num; int x; scanf("%d", &x); 
        MCMF :: add(num, num + n * n, 1, -x);
        MCMF :: add(num, num + n * n, INF, 0);
    }
    REP(i, 1, n) REP(j, 1, n - 1) 
    {
        int x = (i - 1) * n + j;
        MCMF :: add(x + n * n, x + 1, INF, 0);
    }
    REP(i, 1, n - 1) REP(j, 1, n)
    {
        int x = (i - 1) * n + j;
        MCMF :: add(x + n * n, x + n, INF, 0);
    }
    MCMF :: Solve(s, t, flow, cost);
    printf("%d\n", -cost);
    return 0;
}

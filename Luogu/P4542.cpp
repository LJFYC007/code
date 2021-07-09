/***************************************************************
	File name: P4542.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 15时25分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;
const int INF = 0x3f3f3f3f;

int n, m, k, dis[200][200], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int flow, cost, s, t;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

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
    scanf("%d%d%d", &n, &m, &k);
    memset(dis, 0x3f, sizeof(dis)); 
    REP(i, 1, m) 
    { 
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
        add(u, v, w); add(v, u, w);
    }
    REP(k, 0, n)
        REP(i, 0, n) REP(j, 0, n)
            if ( k <= max(i, j) && dis[i][j] > dis[i][k] + dis[k][j] ) 
                dis[i][j] = dis[i][k] + dis[k][j];
    s = n + n + 3; t = n + n + 4;
    REP(i, 0, n)
    {
        MCMF :: add(s, i, !i ? k : 1, 0);
        MCMF :: add(n + i + 1, t, 1, 0);
        REP(j, i + 1, n) MCMF :: add(i, n + j + 1, 1, dis[i][j]);
    }
    MCMF :: Solve(s, t, flow, cost);
    printf("%d\n", cost);
    return 0;
}

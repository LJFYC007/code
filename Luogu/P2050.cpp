/***************************************************************
	File name: P2050.cpp
	Author: ljfcnyali
	Create time: 2019年08月06日 星期二 19时54分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 20000010;
const int INF = 0x3f3f3f3f;	

int n, m, s, t, p[maxn], a[50][110], food[maxn], id[maxn], sum;

inline int js(int i, int j) { return a[i][j]; }

namespace MCMF 
{
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e = 1, W[maxn], F[maxn];
    int dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn], use[maxn];

    inline void add(int u, int v, int w, int f) 
    { 
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
        To[++ e] = u; From[e] = v; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0; F[e] = -f; 
    }

    inline bool BFS(int s, int t)
    {
        // cerr << e << endl;
        REP(i, 1, n) dis[i] = INF, vis[i] = 0;
        dis[t] = INF; vis[t] = 0;
        REP(i, 1, m) use[i] = false;
        REP(i, 1, m) REP(j, 1, food[i]) dis[n + (i - 1) * sum + j] = INF, vis[n + (i - 1) * sum + j] = 0;
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
            if ( u > n && !use[id[u]] ) 
            {
                int x = id[u];
                ++ food[x]; use[x] = true;
               REP(i, 1, n) MCMF :: add(i, n + (x - 1) * sum + food[x], 1, food[x] * js(i, x));
            }
        }
        return true;
    }

    inline void Solve(int s, int t, int &flow, int &cost) 
    {
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
    REP(i, 1, n) { scanf("%d", &p[i]); sum += p[i]; MCMF :: add(s, i, p[i], 0); }
    t = n + sum * m + 1;
    REP(i, 1, m)  REP(j, 1, sum) { MCMF :: add(n + (i - 1) * sum + j, t, 1, 0); id[n + (i - 1) * sum + j] = i; }
    REP(i, 1, n) REP(j, 1, m)
    {
        scanf("%d", &a[i][j]);
        MCMF :: add(i, n + (j - 1) * sum + 1, 1, a[i][j]); 
        food[j] = 1;
    }
    int flow = 0, cost = 0; 
    MCMF :: Solve(s, t, flow, cost);
    printf("%d\n", cost);
    return 0;
}

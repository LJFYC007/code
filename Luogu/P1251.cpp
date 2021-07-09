/***************************************************************
	File name: P1251.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 09时04分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const LL maxn = 2000010;
const LL INF = 100000000000000;	

LL N, r[maxn], p, m, f, n, s, S, T, flow, cost;

namespace MCMF 
{
    LL Begin[maxn], Next[maxn], To[maxn], From[maxn], e = 1, W[maxn], F[maxn];
    LL dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn];

    inline void add(LL u, LL v, LL w, LL f) 
    { 
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
        To[++ e] = u; From[e] = v; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0; F[e] = -f; 
    }

    inline bool BFS(LL s, LL t)
    {
        REP(i, 0, 2 * N + 1) dis[i] = INF; mem(vis);
        dis[s] = 0; a[s] = INF; vis[s] = true;
        queue<LL> Q; Q.push(s);
        while ( !Q.empty() )
        {
            LL u = Q.front(); Q.pop();
            for ( LL i = Begin[u]; i; i = Next[i] ) 
            {
                LL v = To[i];
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

    inline bool Spfa(LL s, LL t, LL &flow, LL &cost)
    {
        if ( !BFS(s, t) ) return false;
        flow += a[t]; cost += a[t] * dis[t];
        LL u = t;
        while ( u != s ) 
        {
            W[pre[u]] -= a[t]; 
            W[pre[u] ^ 1] += a[t];
            u = From[pre[u]];
        }
        return true;
    }

    inline void Solve(LL s, LL t, LL &flow, LL &cost) 
    {
        flow = cost = 0;
        while ( Spfa(s, t, flow, cost) ) ;        
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &N);
    REP(i, 1, N) scanf("%lld", &r[i]);
    scanf("%lld%lld%lld%lld%lld", &p, &m, &f, &n, &s);
    T = 2 * N + 1;
    REP(i, 1, N) 
    {
        MCMF :: add(S, i + N, r[i], 0); MCMF :: add(i, T, r[i], 0); 
        MCMF :: add(S, i, INF, p); 
        if ( i < N ) MCMF :: add(i + N, i + N + 1, INF, 0);
        if ( i + m <= N ) MCMF :: add(i + N, i + m, INF, f);
        if ( i + n <= N ) MCMF :: add(i + N, i + n, INF, s);
    }
    MCMF :: Solve(S, T, flow, cost);
    printf("%lld\n", cost);
    return 0;
}

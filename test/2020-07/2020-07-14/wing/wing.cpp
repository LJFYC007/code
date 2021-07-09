/***************************************************************
	File name: wing.cpp
	Author: ljfcnyali
	Create time: 2020年07月14日 星期二 15时59分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e = 1, F[maxn], W[maxn], dis[maxn], a[maxn], pre[maxn], p[maxn];
bool vis[maxn];

inline void add(int u, int v, int flow, int cost)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; F[e] = flow; W[e] = cost;
    swap(u, v); flow = 0; cost = -cost;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; F[e] = flow; W[e] = cost;
}

inline bool BFS(int s, int t)
{
    REP(i, 1, t) dis[i] = INF; mem(vis); dis[s] = 0;
    queue<int> Q; Q.push(s); a[s] = INF;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( !F[i] ) continue ;
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i]; pre[v] = u;
                a[v] = min(a[u], F[i]); p[v] = i;
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] != INF;
}

inline void DFS(int s, int t, int &flow, int &cost)
{
    int x = t; flow += a[t]; cost += a[t] * dis[t];
    while ( x != s ) 
    {
        F[p[x]] -= a[t];
        F[p[x] ^ 1] += a[t];
        x = pre[x];
    }
}

inline void MCMF(int s, int t, int &flow, int &cost)
{
    flow = cost = 0;
    while ( BFS(s, t) ) DFS(s, t, flow, cost);
}

int n, m, w[210][210], id[210][210], tot, ans;
bool use[210][210];

int main()
{
    freopen("wing.in", "r", stdin);
    freopen("wing.out", "w", stdout);
    scanf("%d%d", &n, &m);
    int S = n * m * 3 + 1, T = S + 1;
    memset(use, 1, sizeof(use));
    REP(i, 1, n) REP(j, 1, m) cin >> use[i][j];
    REP(i, 1, n) REP(j, 1, m) { scanf("%d", &w[i][j]); id[i][j] = ++ tot; ++ tot; ++ tot; }
    int sum = 0;
    REP(i, 1, n) REP(j, 1, m) 
    {
        if ( use[i][j] ) continue ; ans += w[i][j]; ++ sum;
        if ( i + j & 1 ) 
        {
            add(id[i][j], T, 2, 0);
            add(id[i][j] + 1, id[i][j], 1, 0);
            add(id[i][j] + 1, id[i][j], 1, w[i][j]);
            add(id[i][j] + 2, id[i][j], 1, 0);
            add(id[i][j] + 2, id[i][j], 1, w[i][j]);
        }
        else
        {
            add(S, id[i][j], 2, 0);
            add(id[i][j], id[i][j] + 1, 1, 0);
            add(id[i][j], id[i][j] + 1, 1, w[i][j]);
            add(id[i][j], id[i][j] + 2, 1, 0);
            add(id[i][j], id[i][j] + 2, 1, w[i][j]);
        }
    }
    REP(i, 1, n) REP(j, 1, m)
    {
        if ( use[i][j] || (i + j) % 2 == 1 ) continue ;
        if ( !use[i - 1][j] ) add(id[i][j] + 1, id[i - 1][j] + 1, 1, 0);
        if ( !use[i + 1][j] ) add(id[i][j] + 1, id[i + 1][j] + 1, 1, 0);
        if ( !use[i][j - 1] ) add(id[i][j] + 2, id[i][j - 1] + 2, 1, 0);
        if ( !use[i][j + 1] ) add(id[i][j] + 2, id[i][j + 1] + 2, 1, 0);
    }
    int flow, cost; MCMF(S, T, flow, cost);
    // printf("%d\n", flow);
    if ( flow != sum ) puts("-1");
    else printf("%d\n", ans - cost);
    return 0;
}

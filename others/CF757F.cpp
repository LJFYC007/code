/***************************************************************
	File name: CF757F.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 20时32分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int INF = 1e18;

int n, m, s, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], deg[maxn];
int dis[maxn], anc[maxn][20], size[maxn], ans;
bool vis[maxn], use[maxn];
vector<int> p;
queue<int> Q;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void SPFA()
{
    Q.push(s); REP(i, 1, n) dis[i] = INF; dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
}

inline void DFS(int u)
{
    if ( use[u] ) return ; use[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[i] ) continue ;
        if ( dis[v] == dis[u] + W[i] ) 
        { 
            vis[i] = true; ++ deg[v]; 
            DFS(v); 
        }
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &s);
    REP(i, 1, m)
    {
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    SPFA(); mem(vis); DFS(s); Q.push(s); mem(dis);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); p.push_back(u);
        dis[u] = dis[anc[u][0]] + 1;
        REP(i, 1, 18) anc[u][i] = anc[anc[u][i - 1]][i - 1];
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            if ( !vis[i] ) continue ;
            int v = To[i]; -- deg[v];
            if ( !deg[v] ) Q.push(v);
            anc[v][0] = anc[v][0] ? LCA(anc[v][0], u) : u;
        }
    }
    for ( int i = p.size() - 1; i >= 1; -- i ) 
    {
        ++ size[p[i]]; ans = max(ans, size[p[i]]);
        size[anc[p[i]][0]] += size[p[i]];
    }
    printf("%lld\n", ans);
    return 0;
}

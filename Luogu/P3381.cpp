/***************************************************************
	File name: P3381.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 20时43分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, s, t, Begin[maxn], Next[maxn], To[maxn], e = 1, F[maxn], W[maxn];
int dis[maxn], a[maxn], pre[maxn], id[maxn];
bool vis[maxn];

inline void add(int u, int v, int f, int w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
    F[e] = f; W[e] = w;
}

inline bool BFS(int s, int t)
{
    memset(dis, 0x3f, sizeof(dis)); mem(vis); queue<int> Q;
    a[s] = INF; dis[s] = 0; Q.push(s); vis[s] = true;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] && F[i] > 0 ) 
            {
                dis[v] = dis[u] + W[i]; 
                a[v] = min(a[u], F[i]); 
                pre[v] = u; id[v] = i;
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] != INF;
}

inline void DFS(int s, int t, int &flow, int &cost)
{
    flow += a[t]; cost += a[t] * dis[t];
    int u = t;
    while ( u != s ) 
    {
        F[id[u]] -= a[t]; F[id[u] ^ 1] += a[t];
        u = pre[u];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &s, &t);
    REP(i, 1, m) 
    {
        int u, v, f, w; scanf("%d%d%d%d", &u, &v, &f, &w);
        add(u, v, f, w);
        add(v, u, 0, -w);
    }
    int flow = 0, cost = 0;
    while ( BFS(s, t) ) DFS(s, t, flow, cost);
    printf("%d %d\n", flow, cost);
    return 0;
}

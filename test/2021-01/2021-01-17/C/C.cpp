/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 11时21分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 105;

int n, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans, f[maxn][maxn], anc[maxn], S, T;
bool vis[maxn], Vis[maxn];
vector<int> p;
struct node 
{ 
    int u, v, w; 
    node ( int a = 0, int b = 0, int c = 0 ) { u = a; v = b; w = c; } 
} ;
vector<node> b;

namespace MaxCost
{
    const int maxn = 110 * 110;
    const int INF = 0x3f3f3f3f;
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e, W[maxn], F[maxn], dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn];

    inline void add(int u, int v, int w, int f) 
    { 
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
        swap(u, v); f = -f; w = 0;
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
    }

    inline bool BFS(int s, int t)
    {
        REP(i, 1, t) { dis[i] = INF; vis[i] = 0; }
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

    inline bool Spfa(int s, int t, int &flow, int &cost)
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

    inline int Solve()
    {
        e = 1; REP(i, 1, n + 2) Begin[i] = 0;
        int s = n + 1, t = n + 2, flow = 0, cost = 0;
        REP(i, 1, n) if ( Vis[i] ) add(s, i, 1, 0); else add(i, t, 1, 0);
        for ( auto it : b ) add(it.u, it.v, 1, -it.w);
        while ( Spfa(s, t, flow, cost) ) ;        
        return -cost;
    }
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v] = u; DFS1(v, u);
    }
}

inline void DFS2(int u)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
        if ( To[i] != anc[u] ) DFS2(To[i]);
}

inline void DFS3(int u, int fa, int t)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        DFS3(v, u, t);
    }
    b.clear(); 
    // cout << t << " " << u << ":::" << endl;
    for ( auto it : p ) for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        // cout << it << " " << v << " " << f[it][v] << endl;
        b.push_back(node(it, v, f[it][v]));
    }
    f[t][u] = 1 + MaxCost :: Solve();
}

inline void DFS4(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || !vis[v] ) continue ;
        DFS4(v, u); 
    }
    p.clear(); 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || !vis[v] ) continue ;
        p.push_back(v);
    }
    DFS3(T, 0, u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &a[++ n]) ); n /= 2; 
    REP(i, 1, n) { add(a[i] + 1, a[n + i] + 1); add(a[n + i] + 1, a[i] + 1); }
    ++ n; DFS1(1, 0);
    REP(i, 2, n) 
    {
        mem(vis); DFS2(i); REP(j ,1, n) Vis[j] = vis[j];
        REP(j, 1, n) if ( !vis[j] ) { S = i; T = j; DFS4(i, 0); ans = max(ans, f[i][j]); }
    }
    // DFS2(6); REP(j, 1, n) Vis[j] = vis[j]; S = 6; T = 7; DFS4(S, 0); ans = max(ans, f[6][7]);
    printf("%d\n", ans);
    return 0;
}

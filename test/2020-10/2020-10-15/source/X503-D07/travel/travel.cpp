/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 10时30分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ret;
int a[70], dis[maxn], sum, Q[maxn], ans[maxn], anc[maxn][20], dep[maxn];
bool vis[maxn], use[maxn];
struct node { int u, v, w; } Edge[maxn];
map<int, bool> Map;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int LCA(int x, int y)
{
    if ( dep[x] < dep[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dep[anc[x][i]] >= dep[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline void Insert(int x)
{
    for ( int i = 60; i >= 0; -- i ) 
    {
        if ( !((x >> i) & 1) ) continue ;
        if ( !a[i] ) 
        { 
            a[i] = x; ++ sum; ret = 0; Map.clear();
            REP(k, 1, n) 
            {
                int x = dis[k]; if ( x == -1 ) continue ;
                for ( int j = 60; j >= 0; -- j ) 
                    if ( (x >> j) & 1 ) x ^= a[j];
                if ( !Map[x] ) { Map[x] = true; ++ ret; }
            }
            return ; 
        }
        x ^= a[i];
    }
}

inline void DFS(int u, int fa)
{
    vis[u] = true;
    REP(j, 1, 18) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    int x = dis[u];
    for ( int j = 60; j >= 0; -- j )
        if ( (x >> j) & 1 ) x ^= a[j];
    if ( !Map[x] ) { Map[x] = true; ++ ret; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( vis[v] ) Insert(dis[u] ^ dis[v] ^ W[i]);
        else { dep[v] = dep[u] + 1; dis[v] = dis[u] ^ W[i]; anc[v][0] = u; DFS(v, u); }
    }
}

inline void add(int x)
{
    int u = Edge[x].u, v = Edge[x].v, w = Edge[x].w;
    add(u, v, w); add(v, u, w);
    if ( vis[u] && vis[v] ) 
    {
        int t = LCA(u, v);
        Insert(dis[u] ^ dis[v] ^ dis[t] ^ w);
    }
    else if ( vis[u] != vis[v] ) 
    {
        if ( vis[v] ) swap(u, v);
        anc[v][0] = u; dis[v] = dis[u] ^ w; dep[v] = dep[u] + 1; DFS(v, u);
    }
}

signed main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, m) scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
    REP(i, 1, q) { scanf("%lld", &Q[i]); use[Q[i]] = true; } 
    memset(dis, -1, sizeof(dis));
    vis[1] = true; dis[1] = 0; dep[1] = ret = 1; 
    REP(i, 1, m) if ( !use[i] ) add(i); 
    for ( int i = q; i >= 1; -- i ) 
    {
        ans[i] = (1ll << sum) * ret;
        add(Q[i]);
    }
    printf("%lld\n", (1ll << sum) * ret);
    REP(i, 1, q) printf("%lld\n", ans[i]); 
    return 0;
}

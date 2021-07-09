#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const LL INF = 1e18;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int S, Root, Size[maxn], f[maxn], pos;
LL ans, dis[maxn], Min;
struct node 
{ 
    int u, v; LL w; 
    node(int a = 0, int b = 0, LL c = 0) { u = a; v = b; w = c; }
    bool operator < (const node &a) const { return w > a.w; }
} ;
vector<node> Edge;
bool vis[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void GetRoot(int u, int fa)
{
    Size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        GetRoot(v, u); Size[u] += Size[v];
        Max = max(Max, Size[v]);
    }
    Max = max(Max, S - Size[u]);
    if ( Max <= S / 2 ) Root = u;
}

inline void DFS(int u, int fa)
{
    Size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        dis[v] = dis[u] + W[i];
        DFS(v, u); Size[u] += Size[v];
    }
    if ( a[u] + dis[u] < Min ) { Min = a[u] + dis[u]; pos = u; }
}

inline void DFS2(int u, int fa)
{
    Edge.push_back(node(u, pos, Min + a[u] + dis[u]));
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || vis[v] ) continue ;
        DFS2(v, u);
    }
}

inline void Solve(int u)
{
    Min = INF; dis[u] = 0; 
    DFS(u, 0); DFS2(u, 0);
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        S = Size[v]; GetRoot(v, u); Solve(Root);
    }
}

signed main()
{
    freopen("justice.in", "r", stdin);
    freopen("justice.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    S = n; GetRoot(1, 0); Solve(Root);
    REP(i, 1, n) f[i] = i;
    sort(Edge.begin(), Edge.end());
    for ( auto it : Edge ) 
    {
        int fx = find(it.u), fy = find(it.v);
        if ( fx != fy ) { ans += it.w; f[fx] = fy; }
    }
    printf("%lld\n", ans);
    return 0;
}

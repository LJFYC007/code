/***************************************************************
	File name: snow.cpp
	Author: ljfcnyali
	Create time: 2020年11月15日 星期日 11时17分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, q, a[maxn], Begin[maxn], Next[maxn << 1], To[maxn << 1], e, W[maxn << 1], ans, deg[maxn], g[maxn], z[maxn];
int c[maxn], dfn[maxn], id[maxn], size[maxn], son[maxn], f[maxn], cnt, dis[maxn], top[maxn], p[maxn];
struct node { int sum, Min, lazy; } Tree[maxn << 2];
vector<int> Map[maxn];

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy += Tree[root].lazy; Tree[lson].Min += Tree[root].lazy; 
    Tree[rson].lazy += Tree[root].lazy; Tree[rson].Min += Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void PushUp(int root) { Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void Modify2(int root, int l, int r, int pos, int x, int y)
{
    if ( l == r ) { Tree[root].sum = x; Tree[root].Min = y; Tree[root].lazy = 0; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify2(lson, l, Mid, pos, x, y);
    else Modify2(rson, Mid + 1, r, pos, x, y);
    PushUp(root);
}

inline void Fucku(int root, int l, int r, int L, int R, int val)
{
    if ( Tree[root].Min >= val ) return ;
    if ( l == r ) 
    {
        p[id[l]] += (Tree[root].lazy - Tree[root].Min) * Tree[root].sum;
        ans -= Tree[root].Min * Tree[root].sum; 
        Tree[root].Min = INF; Tree[root].sum = Tree[root].lazy = 0; return ;
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Fucku(lson, l, Mid, L, R, val);
    if ( Mid < R ) Fucku(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Query2(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) 
    {
        Tree[root].Min -= val; Tree[root].lazy -= val;
        ans -= val * Tree[root].sum; return ;
    }
    int Mid = l + r >> 1; 
    if ( L <= Mid ) Query2(lson, l, Mid, L, R, val);
    if ( Mid < R ) Query2(rson, Mid + 1, r, L, R, val);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
}

inline int Find(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].lazy * Tree[root].sum;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Find(lson, l, Mid, pos);
    return Find(rson, Mid + 1, r, pos);
}

inline int lowbit(int x) { return x & -x; }
inline void Modify1(int l, int r, int val)
{
    for ( int i = l; i <= n; i += lowbit(i) ) c[i] += val;
    for ( int i = r + 1; i <= n; i += lowbit(i) ) c[i] -= val;
}
inline int Query1(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; f[v] = u; DFS1(v, u); size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    dfn[u] = ++ cnt; id[cnt] = u; top[u] = t; if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) { int v = To[i]; if ( v != f[u] && v != son[u] ) DFS2(v, v); }
}

inline void DFS(int u, int fa)
{
    int Max = 0, sum = 0; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v != fa ) DFS(v, u);
        if ( W[i] > Max ) { Max = W[i]; g[u] = v; }
        sum += W[i]; z[v] = W[i];
    }
    deg[u] = sum; Map[u].push_back(g[u]); Modify2(1, 1, n, dfn[u], 0, INF);
    if ( sum & 1 ) { p[u] += a[u]; -- sum; -- Max; } 
    if ( Max * 2 > sum ) { p[u] += a[u] * (Max * 2 - sum); if ( g[u] != f[u] && g[u] != son[u] ) Modify2(1, 1, n, dfn[u], a[u], Max * 2 - sum); }
}

inline int LCA(int u, int v) { while ( top[u] != top[v] ) { if ( dis[top[u]] < dis[top[v]] ) swap(u, v); u = f[top[u]]; } return dis[u] < dis[v] ? u : v; }

inline void calc(int u)
{
    int x = Query1(dfn[u]), sum = deg[u] + 2 * x, Max = z[u] + x; g[u] = f[u];
    for ( int i = 0; i < Map[u].size(); ++ i ) if ( Map[u][i] != f[u] )
    {
        int val = z[Map[u][i]] + Query1(dfn[Map[u][i]]);
        if ( val > Max ) { Max = val; g[u] = Map[u][i]; }
    }
    ans -= p[u] + Find(1, 1, n, dfn[u]); p[u] = 0; Map[u].clear(); Map[u].push_back(g[u]); Modify2(1, 1, n, dfn[u], 0, INF);
    if ( sum & 1 ) { p[u] += a[u]; -- sum; -- Max; }
    if ( Max * 2 > sum ) { p[u] += a[u] * (Max * 2 - sum); if ( g[u] != f[u] && g[u] != son[u] ) Modify2(1, 1, n, dfn[u], a[u], Max * 2 - sum); }
    ans += p[u];
}

inline void Change(int u, int v, int w)
{
    if ( u == v ) return ; deg[u] += w; deg[v] += w; z[u] += w;
    Map[u].push_back(f[u]); if ( f[u] == v ) { Map[v].push_back(u); return ; } u = f[u];
    while ( top[u] != top[v] ) 
    { 
        Modify1(dfn[top[u]], dfn[u], w); 
        if ( f[top[u]] == v ) { Map[v].push_back(top[u]); return ; }
        u = f[top[u]]; 
    }
    Modify1(dfn[v] + 1, dfn[u], w); Map[v].push_back(son[v]);
}

inline void Maintain(int u, int v, int w) 
{ 
    while ( top[u] != top[v] ) 
    { 
        calc(u); calc(top[u]); 
        Fucku(1, 1, n, dfn[top[u]] + 1, dfn[u] - 1, w);
        Query2(1, 1, n, dfn[top[u]] + 1, dfn[u] - 1, w); 
        u = f[top[u]]; 
    }
    calc(u); calc(v); 
    Fucku(1, 1, n, dfn[v] + 1, dfn[u] - 1, w);
    Query2(1, 1, n, dfn[v] + 1, dfn[u] - 1, w);
}

signed main()
{
    freopen("snow.in", "r", stdin);
    freopen("snow.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    DFS(1, 0); ans = 0; REP(i, 1, n) ans += p[i]; printf("%lld\n", ans);
    while ( q -- ) 
    {
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
        int t = LCA(u, v); Change(u, t, w); Change(v, t, w); w *= 2;
        Maintain(u, t, w); Maintain(v, t, w); printf("%lld\n", ans);
    }
    return 0;
}

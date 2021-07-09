/***************************************************************
	File name: P4175.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 19时49分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 160010;
const int N = 1e8;

struct node { int lson, rson, sum; } Tree[20000010];
int n, m, a[maxn], Root[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int dfn[maxn], cnt, tot, dis[maxn], anc[maxn][20], size[maxn];
vector<int> q[5];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Modify1(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot; Tree[root].sum += val;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify1(ls(root), l, Mid, pos, val);
    else Modify1(rs(root), Mid + 1, r, pos, val);
}

inline int Query1(int l, int r, int k)
{
    if ( l == r ) 
    {
        int ret = 0;
        REP(i, 1, 4) REP(j, 1, q[i].size() - 1) ret += Tree[q[i][j]].sum;
        return ret >= k ? l : -1;
    }
    int Mid = l + r >> 1, ret = 0;
    REP(i, 1, 4) REP(j, 1, q[i].size() - 1) ret += Tree[rs(q[i][j])].sum * (i <= 2 ? 1 : -1);
    REP(i, 1, 4) REP(j, 1, q[i].size() - 1) if ( k <= ret ) q[i][j] = rs(q[i][j]); else q[i][j] = ls(q[i][j]);
    if ( k <= ret ) return Query1(Mid + 1, r, k);
    return Query1(l, Mid, k - ret);
}

inline int lowbit(int x) { return x & -x; }

inline void Modify2(int pos, int x, int val)
{
    for ( int i = pos; i <= n; i += lowbit(i) ) Modify1(Root[i], 0, N, x, val); 
}

inline int Query2(int k)
{
    REP(i, 1, 4) for ( int j = dfn[q[i][0]]; j > 0; j -= lowbit(j) ) q[i].push_back(j);
    return Query1(0, N, k);
}

inline void DFS(int u, int fa)
{
    dfn[u] = ++ cnt; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS(v, u); size[u] += size[v];
    }
    Modify2(dfn[u], a[u], 1); Modify2(dfn[u] + size[u], a[u], -1);
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 17; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 17; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) Root[i] = ++ tot;
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 17) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( m -- ) 
    {
        int k, u, v; scanf("%lld%lld%lld", &k, &u, &v);
        if ( !k ) 
        {
            Modify2(dfn[u], a[u], -1); Modify2(dfn[u] + size[u], a[u], 1);
            a[u] = v;
            Modify2(dfn[u], a[u], 1); Modify2(dfn[u] + size[u], a[u], -1);
            continue ;
        }
        REP(i, 1, 4) q[i].clear(); 
        q[1].push_back(u); q[2].push_back(v); q[3].push_back(LCA(u, v)); q[4].push_back(anc[q[3][0]][0]);
        int ans = Query2(k);
        if ( ans == -1 ) puts("invalid request!");
        else printf("%lld\n", ans);
    }
    return 0;
}

/* 错误时间复杂度
  **************************************************************
	File name: P4175.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 14时58分20秒
**************************************************************
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(root) Tree[root].lson
#define rs(root) Tree[root].rson
typedef long long LL;

const int maxn = 400010;

int f[maxn], g[maxn], n, m, Begin[maxn], Next[maxn], To[maxn], e, tot1, tot2, t[maxn], N;
int dis[maxn], anc[maxn][20], a[maxn], ret, id[maxn], ans[maxn], pos[maxn], block, tot = 1, Root = 1;
bool vis[maxn];

struct node { int sum, lson, rson; } Tree[maxn << 2];
struct node1 { int pos, last, now; } p[maxn];
struct node2 
{ 
    int l, r, t, k, id, lca; 
    bool operator < (const node2 &a) const 
    {
        return pos[l] < pos[a.l] || (pos[l] == pos[a.l] && (pos[r] < pos[a.r] || (pos[r] == pos[a.r] && t < a.t)));
    }
} q[maxn];

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot; Tree[root].sum += val;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
}

inline int Query(int root, int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    if ( k <= Tree[rs(root)].sum ) return Query(rs(root), Mid + 1, r, k);
    return Query(ls(root), l, Mid, k - Tree[rs(root)].sum);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u] = ++ ret; id[ret] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v, u);
    }
    g[u] = ++ ret; id[ret] = u;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 17; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 17; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void add(int pos)
{
    if ( vis[pos] ) Modify(Root, 0, N, a[pos], -1);
    else Modify(Root, 0, N, a[pos], 1);
    vis[pos] ^= 1;
}

inline void Modify(int pos, int val)
{
    if ( vis[pos] ) { add(pos); a[pos] = val; add(pos); }
    else a[pos] = val;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    block = 2000;
    REP(i, 1, n) { scanf("%lld", &a[i]); pos[i] = (i - 1) / block; t[i] = a[i]; N = max(N, a[i]); }
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 17) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        int k, a, b; scanf("%lld%lld%lld", &k, &a, &b);
        if ( !k ) { p[++ tot1].pos = a; p[tot1].last = t[a]; p[tot1].now = t[a] = b; N = max(N, b); }
        else 
        {
            q[++ tot2].t = tot1; q[tot2].id = tot2; q[tot2].k = k; q[tot2].lca = LCA(a, b);
            if ( f[a] > f[b] ) swap(a, b);
            q[tot2].l = q[tot2].lca == a ? f[a] : g[a]; q[tot2].r = f[b];
        }
    }
    sort(q + 1, q + tot2 + 1);
    int L = 1, R = 0, T = 1;
    REP(i, 1, tot2)
    {
        cerr << i << endl;
        while ( T <= q[i].t ) { Modify(p[T].pos, p[T].now); ++ T; }
        while ( T > q[i].t ) { Modify(p[T].pos, p[T].last); -- T; }
        while ( L < q[i].l ) { add(id[L]); ++ L; }
        while ( L > q[i].l ) { -- L; add(id[L]); }
        while ( R < q[i].r ) { ++ R; add(id[R]); }
        while ( R > q[i].r ) { add(id[R]); -- R; }
        if ( q[i].lca != id[L] && q[i].lca != id[R] ) add(q[i].lca);
        ans[q[i].id] = Tree[1].sum >= q[i].k ? Query(Root, 0, N, q[i].k) : -1;
        if ( q[i].lca != id[L] && q[i].lca != id[R] ) add(q[i].lca);
    }
    REP(i, 1, tot2) if ( ans[i] == -1 ) puts("invalid request!"); else printf("%lld\n", ans[i]); 
    return 0;
}
*/

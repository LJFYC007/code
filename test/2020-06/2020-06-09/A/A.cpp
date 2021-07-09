/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2020年06月09日 星期二 07时59分42秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, LL>
#define y1 hhcs_hhakioi_nmsl
#define ls(x) Tree[x].lson
const int _w=(1<<27)-1;
#define rs(x) Tree[x].rson
typedef long long LL;
 
const LL maxn = 4e5 + 10;
 
namespace TreeAndTree
{
    struct node { int lson; LL rson; } Tree[13000000];
    LL Root[maxn], n1, n2, tot;
 
    LL Modify1(LL root, LL l, LL r, LL L, LL R, LL val)
    {
        if ( !(root&_w) ) root |= ++ tot;
        if ( L <= l && r <= R ) { Tree[root&_w].rson += val<<27; return root; }
        LL Mid = l + r >> 1;
        if ( L <= Mid ) ls(root&_w)=Modify1(ls(root&_w), l, Mid, L, R, val);
        if ( Mid < R ) rs(root&_w)=Modify1(rs(root&_w), Mid + 1, r, L, R, val);
        return root;
    }
 
    inline LL Query1(LL root, LL l, LL r, LL pos)
    {
        if ( !(root&_w) ) return 0;
        if ( l == r ) return Tree[root&_w].rson>>27;
        LL Mid = l + r >> 1;
        if ( pos <= Mid ) return (Tree[root&_w].rson>>27) + Query1(ls(root&_w), l, Mid, pos);
        return (Tree[root&_w].rson>>27) + Query1(rs(root&_w), Mid + 1, r, pos);
    }
 
    inline LL lowbit(LL x) { return x & -x; }
 
    inline LL Query(LL x, LL y)
    {
        swap(x, y);
        LL ans = 0;
        for ( LL i = x; i > 0; i -= lowbit(i) ) 
            ans += Query1(Root[i], 1, n2, y);
        return ans;
    }
 
    inline void Modify(LL x1, LL x2, LL y1, LL y2, LL val)
    {
        swap(x1, y1); swap(x2, y2);
        for ( LL i = x1; i <= n1; i += lowbit(i) )
            Root[i]=Modify1(Root[i], 1, n2, y1, y2, val);
        for ( LL i = x2 + 1; i <= n1; i += lowbit(i) )
            Root[i]=Modify1(Root[i], 1, n2, y1, y2, -val);
    }
}
 
LL n, m, N, ty, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans;
int anc[200010][19];
LL p1[maxn], size1[maxn], tot1, p2[maxn], size2[maxn], tot2, f[maxn];
struct node { LL u, v, w; bool operator < (const node &a) const { return w > a.w; } } Edge[maxn];
 
inline LL find(LL x) { return x == f[x] ? x : f[x] = find(f[x]); }
 
inline void add(LL u, LL v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
 
inline void DFS1(LL u, LL fa)
{
    p1[u] = ++ tot1; size1[u] = 1;
    for ( LL i = Begin[u]; i; i = Next[i] ) 
    {
        LL v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size1[u] += size1[v];
    }
}
 
inline void DFS2(LL u, LL fa)
{
    p2[u] = ++ tot2; size2[u] = 1;
    for ( LL i = Begin[u]; i; i = Next[i] ) 
    {
        LL v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u); size2[u] += size2[v]; anc[v][0] = u;
    }
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &ty);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) 
    { 
        scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
        add(Edge[i].u, Edge[i].v); add(Edge[i].v, Edge[i].u); 
    }
 
    DFS1(1, 0); N = n; REP(i, 1, n * 2) f[i] = i;
    mem(Begin); e = 0;
    sort(Edge + 1, Edge + n);
    REP(i, 1, n - 1)
    {
        LL fx = find(Edge[i].u), fy = find(Edge[i].v);
        a[++ N] = Edge[i].w; add(N, fx); add(N, fy); 
        f[fx] = f[fy] = N;
    }
    DFS2(N, 0); REP(j, 1, 18) REP(i, 1, N) anc[i][j] = anc[anc[i][j - 1]][j - 1];
 
    TreeAndTree :: n1 = N; TreeAndTree :: n2 = n;
    REP(i, 1, n) TreeAndTree :: Modify(p1[i], p1[i], p2[i], p2[i], a[i]);
    while ( m -- ) 
    {
        LL op; scanf("%lld", &op);
        if ( op == 1 ) 
        { 
            LL x; scanf("%lld", &x);
            if ( ty == 1 ) x = (x + ans) % n + 1;
            ans = TreeAndTree :: Query(p1[x], p2[x]); printf("%lld\n", ans);
        }
        else
        {
            LL v, d, x; scanf("%lld%lld%lld", &v, &d, &x);
            if ( ty == 1 ) x = (x + ans) % n + 1;
            LL u = x;
            for ( LL j = 18; j >= 0; -- j ) if ( a[anc[u][j]] >= d ) u = anc[u][j];
            TreeAndTree :: Modify(p1[x], p1[x] + size1[x] - 1, p2[u], p2[u] + size2[u] - 1, v);
        }
    }
    return 0;
}

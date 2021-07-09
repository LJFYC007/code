/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月05日 星期五 08时16分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e7 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], w[maxn], f[maxn], dis[maxn];
int size[maxn], p[maxn], top[maxn], id[maxn], tot, son[maxn];
struct node { int sum, lazy; } Tree[maxn << 2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace INIT
{
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
    int tot, N = 10000010;
    struct node { int Min, lson, rson; } Tree[maxn << 3];

    inline void Modify(int &root, int l, int r, int pos, int val)
    {
        if ( !root ) { root = ++ tot; Tree[root].Min = n + 1; }
        Tree[root].Min = min(Tree[root].Min, val);
        if ( l == r ) return ;
        int Mid = l + r >> 1;
        if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
        else Modify(rs(root), Mid + 1, r, pos, val);
    }

    inline int Query(int root, int l, int r, int L, int R)
    {
        if ( !root ) return n + 1;
        if ( L <= l && r <= R ) return Tree[root].Min;
        int Mid = l + r >> 1, ret = n + 1;
        if ( L <= Mid ) ret = min(ret, Query(ls(root), l, Mid, L, R));
        if ( Mid < R ) ret = min(ret, Query(rs(root), Mid + 1, r, L, R));
        return ret;
    }

    inline void INIT()
    {
        int root = 0; Tree[1].Min = n + 1;
        for ( int i = n; i >= 1; -- i ) 
        {
            int pos = Query(root, 0, N, a[i] + 1, N);
            add(pos, i);
            Modify(root, 0, N, a[i], i);
        }
    }
}

#define lson root << 1
#define rson root << 1 | 1

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].sum = w[id[l]]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) 
    {
        if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
        x = f[top[x]];
    }
    return dis[x] < dis[y] ? x : y;
}

inline int Solve(int x, int y)
{
    int ret = 0;
    while ( top[x] != top[y] ) 
    {
        if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
        ret += Query(1, 1, n + 1, p[top[x]], p[x]);
        x = f[top[x]];
    }
    if ( dis[x] > dis[y] ) swap(x, y);
    ret += Query(1, 1, n + 1, p[x], p[y]);
    return ret;
}

inline void DFS1(int u)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        dis[v] = dis[u] + 1; f[v] = u; 
        DFS1(v); size[u] += size[v];
        if ( size[v] > size[son[u]] ) son[u] = v;
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t; p[u] = ++ tot; id[tot] = u;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) scanf("%lld", &w[i]);
    INIT :: INIT();
    dis[n + 1] = 1; DFS1(n + 1); DFS2(n + 1, n + 1); Build(1, 1, n + 1);
    REP(i, 1, m) 
    {
        int op, x, y; scanf("%lld%lld%lld", &op, &x, &y);
        if ( op == 2 ) 
        {
            int t = LCA(x, y), ans = Solve(x, y);
            if ( t == x || t == y ) { t = f[t]; ans += w[t]; }
            if ( t == n + 1 ) puts("?");
            else printf("%lld\n", ans);
        }
    }
    return 0;
}

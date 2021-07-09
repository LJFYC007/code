/***************************************************************
	File name: P5327.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 16时43分59秒
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

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, ans, Root[maxn], a[maxn];
int size[maxn], top[maxn], son[maxn], p[maxn], id[maxn], tot, f[maxn], dis[maxn];
struct node { int lson, rson, num, sum, Min, Max; } Tree[maxn << 5];

inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) { if ( dis[top[x]] < dis[top[y]] ) swap(x, y); x = f[top[x]]; }
    return dis[x] < dis[y] ? x : y;
}

inline void PushUp(int root) 
{ 
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum - dis[LCA(id[Tree[ls(root)].Max], id[Tree[rs(root)].Min])];
    Tree[root].Min = Tree[ls(root)].Min ? Tree[ls(root)].Min : Tree[rs(root)].Min;
    Tree[root].Max = Tree[rs(root)].Max ? Tree[rs(root)].Max : Tree[ls(root)].Max;
}

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) 
    { 
        Tree[root].num += val; 
        Tree[root].sum = Tree[root].num > 0 ? dis[id[l]] : 0;
        Tree[root].Min = Tree[root].Max = Tree[root].num > 0 ? l : 0;
        return ; 
    }
    int Mid = l + r >> 1; 
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Merge(int &p, int q, int l, int r)
{
    if ( !p || !q ) { p += q; return ; }
    if ( l == r ) 
    { 
        Tree[p].num += Tree[q].num; 
        Tree[p].sum = Tree[p].num > 0 ? dis[id[l]] : 0;
        Tree[p].Min = Tree[p].Max = Tree[p].num > 0 ? l : 0;
        return ; 
    }
    int Mid = l + r >> 1;
    Merge(ls(p), ls(q), l, Mid);
    Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(p);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; dis[v] = dis[u] + 1; DFS1(v, u);
        size[u] += size[v]; if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
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

inline void DFS3(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS3(v, u);
        Merge(Root[u], Root[v], 1, n);
    }
    // printf("%lld %lld %lld\n", u, Tree[Root[u]].sum, dis[LCA(id[Tree[Root[u]].Min], id[Tree[Root[u]].Max])]);
    ans += Tree[Root[u]].sum - dis[LCA(id[Tree[Root[u]].Min], id[Tree[Root[u]].Max])];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    REP(i, 1, m)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        Modify(Root[u], 1, n, p[u], 1);
        Modify(Root[u], 1, n, p[v], 1);
        Modify(Root[v], 1, n, p[u], 1);
        Modify(Root[v], 1, n, p[v], 1);
        int x = LCA(u, v);
        Modify(Root[x], 1, n, p[u], -1);
        Modify(Root[x], 1, n, p[v], -1);
        Modify(Root[f[x]], 1, n, p[u], -1);
        Modify(Root[f[x]], 1, n, p[v], -1);
    }
    DFS3(1, 0);
    printf("%lld\n", ans / 2);
    return 0;
}

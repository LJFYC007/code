/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年06月08日 星期一 09时11分15秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;
 
const int maxn = 1e6 + 10;
const int INF = 2e9;
 
int n, m, son[maxn][2], val[maxn], f[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], size[maxn], top[maxn], p[maxn], id[maxn], tot, Son[maxn], num[maxn];
pii w1[maxn], w2[maxn];
struct node { pii x, y; bool lazy; } Tree[maxn];
 
pii operator + (pii x, pii y) { return pii(max(x.first, y.first), min(x.second, y.second)); }
 
inline void PushUp(int root) 
{ 
    Tree[root].x = Tree[lson].x + Tree[rson].x; 
    Tree[root].y = Tree[lson].y + Tree[rson].y; 
}

inline void PushTag(int root) { Tree[root].lazy ^= 1; swap(Tree[root].x, Tree[root].y); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson); PushTag(rson); Tree[root].lazy = false;
}
 
inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].x = w1[id[l]]; Tree[root].y = w2[id[l]]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline bool Ask(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].lazy;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Ask(lson, l, Mid, pos);
    return Ask(rson, Mid + 1, r, pos);
}
 
inline void Modify(int root, int l, int r, int pos, pii x, pii y)
{
    if ( l == r ) { Tree[root].x = x; Tree[root].y = y; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, x, y);
    else Modify(rson, Mid + 1, r, pos, x, y);
    PushUp(root);
}

inline void Update(int root, int l, int r, int L, int R)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) { PushTag(root); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Update(lson, l, Mid, L, R);
    if ( Mid < R ) Update(rson, Mid + 1, r, L, R);
    PushUp(root);
}
 
inline pii Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].x;
    int Mid = l + r >> 1; pii x = pii(-1, INF); PushDown(root);
    if ( L <= Mid ) x = x + Query(lson, l, Mid, L, R);
    if ( Mid < R ) x = x + Query(rson, Mid + 1, r, L, R);
    return x;
}
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
 
inline void DFS1(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        DFS1(v, u); size[u] += size[v];
        if ( size[v] > size[Son[u]] ) Son[u] = v;
    }
}
 
inline void DFS2(int u, int t)
{
    top[u] = t; p[u] = ++ tot; id[tot] = u;
    if ( Son[u] ) DFS2(Son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == Son[u] ) continue ;
        DFS2(v, v);
    }
}
 
inline pii Solve(int x)
{
    pii ret = pii(-1, INF);
    while ( top[x] != 1 ) { ret = ret + Query(1, 1, n, p[top[x]], p[x]); x = f[top[x]]; }
    ret = ret + Query(1, 1, n, p[1], p[x]);
    return ret;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    {
        scanf("%d%d%d", &val[i], &son[i][0], &son[i][1]);
        if ( son[i][0] ) 
        { 
            f[son[i][0]] = i; add(i, son[i][0]); 
            w1[son[i][0]] = pii(-1, val[i]);
            w2[son[i][0]] = pii(val[i], INF);
        }
        if ( son[i][1] ) 
        { 
            f[son[i][1]] = i; add(i, son[i][1]); 
            w1[son[i][1]] = pii(val[i], INF);
            w2[son[i][1]] = pii(-1, val[i]);
        }
    }
    w1[1] = w2[1] = pii(-1, INF); dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    while ( m -- ) 
    {
        int op, x; scanf("%d%d", &op, &x);
        if ( op == 1 ) 
        {
            scanf("%d", &val[x]);
            pii a = pii(-1, val[x]), b = pii(val[x], INF);
            if ( Ask(1, 1, n, p[x]) ^ num[x] ) swap(a, b);
            if ( son[x][0] ) Modify(1, 1, n, p[son[x][0]], a, b);
            if ( son[x][1] ) Modify(1, 1, n, p[son[x][1]], b, a);
        }
        else if ( op == 2 ) { num[x] ^= 1; Update(1, 1, n, p[x] + 1, p[x] + size[x] - 1); }
        else
        {
            pii w = Solve(x);
            // printf("%d %d\n", w.first, w.second);
            if ( w.first < val[x] && val[x] < w.second ) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}

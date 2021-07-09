/***************************************************************
	File name: cw.cpp
	Author: ljfcnyali
	Create time: 2020年05月28日 星期四 10时04分38秒
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

int n, m1, m2, q, col[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans[maxn], a[maxn];

namespace SplitTree
{
    int son[maxn], size[maxn], top[maxn], f[maxn], p[maxn], id[maxn], tot, dis[maxn];
    struct node 
    { 
        int sum, lcol, rcol; 
        node ( int a = 0, int b = 0, int c = 0 ) { sum = a; lcol = b; rcol = c; }
    } Tree[maxn];
    node operator + (node a, node b) 
    {
        if ( a.sum == 0 ) return b;
        if ( b.sum == 0 ) return a;
        node c = node(a.sum + b.sum, a.lcol, b.rcol);
        if ( a.rcol == b.lcol ) -- c.sum;
        return c;
    }

    inline void DFS1(int u, int fa)
    {
        size[u] = 1; int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            dis[v] = dis[u] + 1; f[v] = u; DFS1(v, u);
            size[u] += size[v]; if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        }
    }

    inline void DFS2(int u, int t)
    {
        p[u] = ++ tot; id[tot] = u; top[u] = t;
        if ( son[u] ) DFS2(son[u], t);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
            DFS2(v, v);
        }
    }

    inline void PushUp(int root) { Tree[root] = Tree[lson] + Tree[rson]; }

    inline void Build(int root, int l, int r)
    {
        if ( l == r ) { Tree[root] = node(1, col[id[l]], col[id[l]]); return ; }
        int Mid = l + r >> 1;
        Build(lson, l, Mid); Build(rson, Mid + 1, r);
        PushUp(root);
    }

    inline void Modify(int root, int l, int r, int pos, int val)
    {
        if ( l == r ) { Tree[root] = node(1, val, val); return ; }
        int Mid = l + r >> 1;
        if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
        else Modify(rson, Mid + 1, r, pos, val);
        PushUp(root);
    }

    inline node Query(int root, int l, int r, int L, int R)
    {
        if ( L <= l && r <= R ) return Tree[root];
        int Mid = l + r >> 1; node ret;
        if ( L <= Mid ) ret = ret + Query(lson, l, Mid, L, R);
        if ( Mid < R ) ret = ret + Query(rson, Mid + 1, r, L, R);
        return ret;
    }

    inline void INIT() { dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n); }

    inline int LCA(int x, int y)
    {
        while ( top[x] != top[y] ) 
        {
            if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
            x = f[top[x]];
        }
        return dis[x] < dis[y] ? x : y;
    }

    inline int Solve(int u, int v)
    {
        int t = LCA(u, v); node ret1, ret2;
        while ( top[u] != top[t] ) 
        {
            ret1 = Query(1, 1, n, p[top[u]], p[u]) + ret1;
            u = f[top[u]];
        }
        ret1 = Query(1, 1, n, p[t], p[u]) + ret1;
        while ( top[v] != top[t] ) 
        {
            ret2 = Query(1, 1, n, p[top[v]], p[v]) + ret2;
            v = f[top[v]];
        }
        ret2 = Query(1, 1, n, p[t], p[v]) + ret2;
        return ret1.sum + ret2.sum - 1;
    }
}

namespace Mo
{
    int block, pos[maxn], f[maxn], g[maxn], tot, num[maxn], cnt[maxn], id[maxn], vis[maxn], ret;
    struct node1 
    { 
        int t, l, r, id;
        node1(){}
        node1(int a, int b, int c, int d) { t = a; l = b; r = c; id = d; }
        bool operator < (const node1 &x) const 
        {
            return pos[l] < pos[x.l] || (pos[l] == pos[x.l] && (pos[r] < pos[x.r] || (pos[r] == pos[x.r] && t < x.t)));
        }   
    } a[maxn];
    struct node2 
    { 
        int t, pos, lst, now; 
        node2(){}
        node2(int a, int b, int c, int d) { t = a; pos = b; lst = c; now = d; }
    } b[maxn];

    inline void DFS(int u, int fa)
    {
        f[u] = ++ tot; id[tot] = u;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS(v, u);
        }
        g[u] = ++ tot; id[tot] = u;
    }

    inline void INIT() { block = pow(n, 2.0 / 3); DFS(1, 0); REP(i, 1, tot) pos[i] = (i - 1) / block + 1; }

    inline void add(int x)
    {
        if ( vis[x] ) 
        { 
            -- num[cnt[col[x]]];
            -- cnt[col[x]]; 
            ++ num[cnt[col[x]]];
            while ( num[ret] == 0 ) -- ret;
        }
        else 
        {
            -- num[cnt[col[x]]];
            ++ cnt[col[x]]; 
            ++ num[cnt[col[x]]];
            while ( num[ret + 1] > 0 ) ++ ret;
        }
        vis[x] ^= 1;
    }

    inline void Modify(int pos, int val)
    {
        if ( vis[pos] ) { add(pos); col[pos] = val; add(pos); }
        else col[pos] = val;
    }

    inline void Solve()
    {
        sort(a + 1, a + m1 + 1); 
        int L = 0, R = 0, t = 0;
        REP(i, 1, m1)
        {
            while ( t < a[i].t ) { ++ t; Modify(b[t].pos, b[t].now); }
            while ( t > a[i].t ) { Modify(b[t].pos, b[t].lst); -- t; }
            while ( L < a[i].l ) { add(id[L]); ++ L; }
            while ( L > a[i].l ) { -- L; add(id[L]); } 
            while ( R < a[i].r ) { ++ R; add(id[R]); }
            while ( R > a[i].r ) { add(id[R]); -- R; }
            int u = id[L], v = id[R], x = SplitTree :: LCA(u, v);
            if ( x != u && x != v ) add(x);
            ans[a[i].id] = ret;
            if ( x != u && x != v ) add(x);
        }
    }
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

int main()
{
    freopen("cw.in", "r", stdin);
    freopen("cw.out", "w", stdout);
    scanf("%d%d", &n, &q);
    REP(i, 1, n) { read(col[i]); ++ col[i]; a[i] = col[i]; }
    REP(i, 1, n - 1) { int u, v; read(u); read(v);; add(u, v); add(v, u); }
    SplitTree :: INIT(); Mo :: INIT();
    REP(i, 1, q) ans[i] = -1;
    REP(i, 1, q)
    {
        int t, x, y; read(t); read(x); read(y);
        if ( t == 2 ) ans[i] = SplitTree :: Solve(x, y);
        else if ( t == 1 ) 
        {
            ++ y; ++ m2; Mo :: b[m2] = Mo :: node2(m2, x, a[x], y);
            a[x] = y;
            SplitTree :: Modify(1, 1, n, SplitTree :: p[x], y);
        }
        else 
        {
            if ( Mo :: f[x] > Mo :: f[y] ) swap(x, y);
            int l = SplitTree :: LCA(x, y) == x ? Mo :: f[x] : Mo :: g[x], r = Mo :: f[y]; 
            Mo :: a[++ m1] = Mo :: node1(m2, l, r, i);
        }
    }
    Mo :: Solve();
    REP(i, 1, q) if ( ans[i] != -1 ) printf("%d\n", ans[i]);
    return 0;
}

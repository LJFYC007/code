/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 14时05分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, p[maxn], id[maxn], ans[maxn];
struct node1 { int opt, l, r, val, id, pos; } q[maxn];
struct NODE
{
    struct node { int sum, lazy, len; bool tag; } Tree[maxn << 4];

    inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

    inline void PushDown(int root)
    {
        if ( Tree[root].tag ) 
        {
            Tree[root].tag = false;
            Tree[lson].tag = Tree[rson].tag = true;
            Tree[lson].sum = Tree[rson].sum = Tree[lson].lazy = Tree[rson].lazy = 0;
        }
        if ( !Tree[root].lazy ) return ;
        int x = Tree[root].lazy; Tree[root].lazy = 0;
        Tree[lson].lazy += x; Tree[rson].lazy += x;
        Tree[lson].sum += x * Tree[lson].len;
        Tree[rson].sum += x * Tree[rson].len;
    }

    inline void Build(int root, int l, int r)
    {
        Tree[root].len = r - l + 1;
        if ( l == r ) return ;
        int Mid = l + r >> 1;
        Build(lson, l, Mid); Build(rson, Mid + 1, r);
    }

    inline void Modify(int root, int l, int r, int L, int R, int val)
    {
        if ( L <= l && r <= R ) 
        { 
            Tree[root].lazy += val; 
            Tree[root].sum += Tree[root].len * val; 
            return ; 
        }
        PushDown(root);
        int Mid = l + r >> 1;
        if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
        if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
        PushUp(root);
    }

    inline int Query(int root, int l, int r, int L, int R)
    {
        if ( !Tree[root].sum || (L <= l && r <= R) ) return Tree[root].sum;
        PushDown(root);
        int Mid = l + r >> 1, sum = 0;
        if ( L <= Mid ) sum += Query(lson, l, Mid, L, R);
        if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R);
        return sum;
    }
} A, B;

inline int cmp(node1 a, node1 b) { return a.pos < b.pos; }

inline void CDQ(int l, int r)
{
    if ( l >= r ) return ;
    int Mid = l + r >> 1; 
    CDQ(l, Mid); CDQ(Mid + 1, r);
    sort(q + l, q + Mid + 1, cmp);
    sort(q + Mid + 1, q + r + 1, cmp);
    int L = l;
    A.Tree[1].tag = true; A.Tree[1].sum = A.Tree[1].lazy = 0;
    B.Tree[1].tag = true; B.Tree[1].sum = B.Tree[1].lazy = 0;
    REP(i, Mid + 1, r) 
    {
        if ( q[i].opt == 1 ) continue ;
        while ( q[L].pos <= q[i].pos && L <= Mid ) 
        {
            if ( q[L].opt == 1 ) A.Modify(1, 1, n, q[L].l, q[L].r, q[L].val);
            ++ L;
        }
        ans[q[i].id] += A.Query(1, 1, n, q[i].l, q[i].r);
    }
    L = Mid;
    for ( int i = r; i >= Mid + 1; -- i ) 
    {
        if ( q[i].opt == 2 ) continue ;
        while ( q[L].pos >= q[i].pos && L >= l ) 
        {
            if ( q[L].opt == 2 ) 
                B.Modify(1, 1, n, q[L].l, q[L].r, 1);
            -- L;
        }
        ans[q[i].id] += B.Query(1, 1, n, q[i].l, q[i].r) * q[i].val;
    }
}

signed main()
{
    freopen("generator.in", "r", stdin);
    freopen("generator.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, m) { scanf("%lld", &p[i]); id[p[i]] = i; }
    REP(i, 1, n) if ( !id[i] ) { id[i] = 1; p[1] = i; break ; }
    REP(i, 1, m) 
    {
        scanf("%lld%lld%lld", &q[i].opt, &q[i].l, &q[i].r); 
        if ( q[i].opt == 1 ) scanf("%lld", &q[i].val); 
        q[i].id = id[i]; q[i].pos = i;
    }
    A.Build(1, 1, n); B.Build(1, 1, n);
    sort(q + 1, q + m + 1, [](node1 a, node1 b) { return a.id < b.id; });
    CDQ(1, m);
    REP(i, 1, m) printf("%lld\n", ans[i] += ans[i - 1]);
    return 0;
}

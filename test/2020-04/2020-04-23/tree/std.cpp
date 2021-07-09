/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年04月26日 星期日 20时49分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define fa(x) Tree[x].fa
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, p[maxn];
stack<int> Stack;
struct node { int son[2], val, sum1, sum2, fa, lazy; } Tree[maxn];
struct Node { bool sum; int Edge; } tree[maxn];

inline bool Isroot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline void Update(int root) { Tree[root].lazy ^= 1; swap(ls(root), rs(root)); }

inline void PushUp(int root) { Tree[root].sum1 = Tree[ls(root)].sum1 + Tree[rs(root)].sum1 + Tree[root].val + Tree[root].sum2; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ; Tree[root].lazy ^= 1;
    if ( ls(root) ) Update(ls(root));
    if ( rs(root) ) Update(rs(root));
}

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !Isroot(y) ) Tree[z].son[rs(z) == y] = x;
    fa(x) = z; fa(y) = x;
    if ( w ) fa(w) = y;
    Tree[y].son[k] = w; Tree[x].son[!k] = y;
    PushUp(y); PushUp(x); PushUp(z);
}

inline void Splay(int x)
{
    int y = x, z; Stack.push(y);
    while ( !Isroot(y) ) { y = fa(y); Stack.push(y); }
    while ( !Stack.empty() ) { PushDown(Stack.top()); Stack.pop(); }
    while ( !Isroot(x) ) 
    {
        y = fa(x); z = fa(y);
        if ( !Isroot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
    PushUp(x);
}

inline void Access(int root)
{
    for ( int x = 0; root; x = root, root = fa(root) ) 
    {
        Splay(root);
        Tree[root].sum2 += Tree[rs(root)].sum1 - Tree[x].sum1;
        rs(root) = x;
        PushUp(root);
    }
}

inline void MakeRoot(int root) { Access(root); Splay(root); Update(root); }

inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; }

inline void Link(int u, int v) { MakeRoot(u); Access(v); Splay(v); fa(u) = v; Tree[v].sum2 += Tree[u].sum1; PushUp(v); }

inline void Cut(int u, int v) { MakeRoot(u); Access(v); Splay(v); fa(u) = ls(v) = 0; PushUp(v); }

inline void Change(int root, int val) { MakeRoot(root); Tree[root].val = val; PushUp(root); }

inline void pushup(int root) { tree[root].sum = tree[lson].sum & tree[rson].sum & (tree[root].Edge == root / 2); }

inline void pushdown(int root, int l, int r) 
{ 
    if ( tree[root].sum == true ) return ; 
    if ( tree[root].Edge != root / 2 ) 
    { 
        Cut(tree[root].Edge, root); Link(root / 2, root); 
        tree[root].Edge = root / 2; 
    }
    if ( l == r ) { tree[root].sum = true; return ; }
    int Mid = l + r >> 1;
    pushdown(lson, l, Mid); pushdown(rson, Mid + 1, r);  
    pushup(root);
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { p[l] = root; if ( l != 1 ) tree[root].sum = true; return ; } 
    int Mid = l + r >> 1;
    if ( l != 1 ) { Link(root, lson); tree[lson].Edge = root; }
    Link(root, rson); tree[rson].Edge = root;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    pushup(root);
    // printf("%d %d %d %d\n", root, tree[root].sum, l, r);
}

inline void Modify(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) 
    {
        Cut(tree[root].Edge, root); tree[root].Edge = x; Link(x, root);
        if ( l == r ) { tree[root].sum = false; return ; }
        int Mid = l + r >> 1;
        pushdown(lson, l, Mid); pushdown(rson, Mid + 1, r); 
        pushup(root); return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
    pushup(root);
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    Build(1, 1, n);
    REP(i, 1, n) { int x; scanf("%d", &x); Change(p[i], x); }
    Modify(1, 1, n, 2, n, p[1]);
    /*
    REP(i, 1, n)
    {
        int x = p[i];
        MakeRoot(p[1]); Access(x); 
        printf("%d ", Tree[x].sum1 - Tree[ls(x)].sum1); 
    }
    puts("");
    */
    while ( m -- ) 
    {
        int op, x, l, r;
        scanf("%d%d", &op, &x); x = p[x];
        if ( op == 0 ) 
        { 
            scanf("%d%d", &l, &r); 
            Modify(1, 1, n, l, r, x);
        }
        if ( op == 1 ) { int val; scanf("%d", &val); Change(x, val); }
        if ( op == 2 ) { MakeRoot(p[1]); Access(x); printf("%d\n", Tree[x].sum1 - Tree[ls(x)].sum1); }
    }
    return 0;
}

/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年06月04日 星期二 11时32分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 400010;

int Begin[maxn], Next[maxn], To[maxn], e;
int size[maxn], son[maxn], f[maxn], id[maxn], p[maxn], top[maxn], dis[maxn];
int n, m, a[maxn], cnt, Lu, Lv, R, L;

struct node
{
    int l, r, sum, lazy, lc, rc;
} Tree[maxn];

inline void Push_up(int root) 
{
    Tree[root].lc = Tree[lson].lc; Tree[root].rc = Tree[rson].rc;
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
    if ( Tree[lson].rc == Tree[rson].lc ) Tree[root].sum --;
}

inline void Push_down(int root)
{
    if ( Tree[root].lazy == -1 ) return ;
    if ( Tree[root].l == Tree[root].r ) { Tree[root].lazy = -1; return ; }
    Tree[lson].sum = Tree[rson].sum = 1;
    Tree[lson].lazy = Tree[rson].lazy = Tree[root].lazy;
    Tree[lson].lc = Tree[lson].rc = Tree[rson].lc = Tree[rson].rc = Tree[root].lazy;
    Tree[root].lazy = -1;
}

inline void Build(int root, int l, int r)
{
    Tree[root].l = l; Tree[root].r = r; Tree[root].lazy = -1;
    if ( l == r ) 
    {
        Tree[root].sum = 1; Tree[root].lc = Tree[root].rc = a[p[l]];
        return ;
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Push_up(root);
}

inline void Update(int root, int l, int r, int val)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        Tree[root].lazy = Tree[root].lc = Tree[root].rc = val;
        Tree[root].sum = 1;
        return ;
    }
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
}

inline int Query(int root, int l, int r)
{
    Push_down(root);
   // cerr << root << " " << Tree[root].lc << " " << Tree[root].rc << " " << Tree[root].sum << " " << Tree[root].lazy << endl;
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    { 
        if ( L == -1 ) L = Tree[root].lc; 
        R = Tree[root].rc; 
        return Tree[root].sum; 
    }
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( r <= Mid ) return Query(lson, l, r);
    else if ( l > Mid ) return Query(rson, l, r);
    else
    {
        int sum = Query(lson, l, r) + Query(rson, l, r);
        if ( Tree[lson].rc == Tree[rson].lc ) -- sum;
        return sum;
    }
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int x)
{
    dis[u] = ++ x; size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( dis[v] ) continue ;
        f[v] = u; DFS1(v, x);
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t; id[u] = ++ cnt; p[cnt] = u;
    if ( !son[u] ) return ;
    DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( f[u] == v || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void Update1(int u, int v, int val)
{
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        Update(1, id[top[u]], id[u], val);
        u = f[top[u]];
    }
    if ( !id[u] || !id[v] ) return ;
    if ( dis[u] > dis[v] ) swap(u, v);
    Update(1, id[u], id[v], val);
}

inline int Query1(int u, int v)
{
    int ans = 0; Lu = Lv = -1;
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) { swap(u, v); swap(Lu, Lv); }
        L = R = -1;
        ans += Query(1, id[top[u]], id[u]);
    //    cerr << Lu << " " << R << " " << L << endl;
        if ( Lu != -1 && Lu == R ) -- ans;
        Lu = L;
        u = f[top[u]];
    }
    if ( !id[u] || !id[v] ) return ans;
    if ( dis[u] > dis[v] ) { swap(u, v); swap(Lu, Lv); }
  //      cerr << id[u] << " " << id[v] << endl;
    L = R = -1;
    ans += Query(1, id[u], id[v]);
    if ( Lu != -1 && Lu == L ) -- ans;
    if ( Lv != -1 && Lv == R ) -- ans;
//        cerr << ans << endl;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
//    REP(i, 1, n) printf("%d ", id[i]);
    REP(i, 1, m)
    {
        getchar(); getchar(); char c = getchar();
 //       cerr << c << endl;
        if ( c == 'C' ) 
        {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            Update1(a, b, c);
        }
        else 
        {
            int a, b; scanf("%d%d", &a, &b);
            printf("%d\n", Query1(a, b));
        }
    }
    return 0;
}

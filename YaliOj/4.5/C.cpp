/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年06月04日 星期二 09时51分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 400010;

int Begin[maxn], To[maxn], e, Next[maxn];
int dis[maxn], size[maxn], f[maxn], id[maxn], son[maxn], top[maxn];
int n, m, cnt, ans;

struct node
{
    int l, r, len, val, lazy;
} Tree[maxn];

inline void Push_up(int root) { Tree[root].val = Tree[lson].val + Tree[rson].val; }

inline void Push_down(int root)
{
    if ( Tree[root].lazy == 0 ) return ;
    int val = Tree[root].lazy; Tree[root].lazy = 0;
    if ( Tree[root].len == 1 ) return ;
    Tree[lson].lazy = val;
    if ( val == 2 ) Tree[lson].val = 0; else Tree[lson].val = Tree[lson].len;
    Tree[rson].lazy = val;
    if ( val == 2 ) Tree[rson].val = 0; else Tree[rson].val = Tree[rson].len;
}

inline void Build(int root, int l, int r)
{
    Tree[root].l = l; Tree[root].r = r; Tree[root].len = r - l + 1;
    Tree[root].lazy = 0;
    if ( l == r ) { Tree[root].val = 0; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Push_up(root);
}

inline void Update(int root, int l, int r, int val)
{
    Push_down(root);
 //   printf("%d %d %d %d\n", Tree[root].l, Tree[root].r, Tree[root].val, Tree[root].lazy);
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        if ( val == 1 )
        {
            ans += Tree[root].len - Tree[root].val;
            Tree[root].val = Tree[root].len;
        }
        else
        {
            ans += Tree[root].val;
            Tree[root].val = 0;
        }
        Tree[root].lazy = val;
    //    printf("%d %d %d %d\n", Tree[root].l, Tree[root].r, Tree[root].val, Tree[root].lazy);
        return ;
    }
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
 //   printf("%d %d %d %d\n", Tree[root].l, Tree[root].r, Tree[root].val, Tree[root].lazy);
}

inline int Query(int root, int l, int r)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) return Tree[root].val;
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1, sum = 0;
    if ( l <= Mid ) sum += Query(lson, l, r);
    if ( Mid < r ) sum += Query(rson, l, r);
    return sum;
}

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS1(int u, int x)
{
    dis[u] = ++ x; size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] ) continue ;
        f[v] = u;
        DFS1(v, x); if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ cnt; top[u] = t;
    if ( !son[u] ) return ;
    DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] || v == f[u] ) continue ;
        DFS2(v, v);
    }
}

inline void Update1(int u)
{
    int v = 1; ans = 0;
    while ( u ) 
    {
//        printf("%d %d %d %d\n", u, top[u], id[u], id[top[u]]);
        Update(1, id[top[u]], id[u], 1); 
        u = f[top[u]];
    }
    printf("%d\n", ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u = i + 1, v; scanf("%d", &v); add(v + 1, u); add(u, v + 1); }
    DFS1(1, 0); DFS2(1, 1);
    Build(1, 1, n);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        char s[100]; scanf("%s", s);
        if ( s[0] == 'i' ) 
        {
            int x; scanf("%d", &x);
            Update1(x + 1);
        }
        else 
        {
            int x; scanf("%d", &x); ++ x;
            ans = 0; Update(1, id[x], id[x] + size[x] - 1, 2);
            printf("%d\n", ans);
        }
    }
    return 0;
}

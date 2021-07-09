/***************************************************************
	File name: P3313.cpp
	Author: ljfcnyali
	Create time: 2019年06月30日 星期日 09时03分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson Tree[root].l
#define rson Tree[root].r
#define max maxx

const int maxn = 30000010;

int Begin[maxn], Next[maxn], To[maxn], e, Root[maxn];
int W[maxn], C[maxn], p[maxn], dis[maxn], fa[maxn], tot;
int n, m, id[maxn], cnt, son[maxn], size[maxn], top[maxn];

struct node
{
    int Max, sum, l, r;
} Tree[maxn];

inline int maxx(int a, int b) { return a > b ? a : b; }

inline void Push_up(int root)
{
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline void Update(int &root, int l, int r, int x, int val)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) { Tree[root].Max = Tree[root].sum = val; return ; }
    int Mid = l + r >> 1;
    if ( x <= Mid ) Update(lson, l, Mid, x, val);
    else Update(rson, Mid + 1, r, x, val);
    Push_up(root);
}

inline int Query_sum(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int sum = 0, Mid = l + r >> 1;
    if ( L <= Mid ) sum += Query_sum(lson, l, Mid, L, R);
    if ( Mid < R ) sum += Query_sum(rson, Mid + 1, r, L, R);
    return sum;
}

inline int Query_Max(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Max = 0, Mid = l + r >> 1;
    if ( L <= Mid ) Max = max(Max, Query_Max(lson, l, Mid, L, R));
    if ( Mid < R ) Max = max(Max, Query_Max(rson, Mid + 1, r, L, R));
    return Max;
}

inline void Remove(int root, int l, int r, int x)
{
    if ( !root ) return ;
    if ( l == r ) { Tree[root].sum = Tree[root].Max = 0; return ; }
    int Mid = l + r >> 1;
    if ( x <= Mid ) Remove(lson, l, Mid, x);
    else Remove(rson, Mid + 1, r, x);
    Push_up(root);
}

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS1(int u)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa[u] ) continue ;
        dis[v] = dis[u] + 1; fa[v] = u;
        DFS1(v);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    id[++ cnt] = u; p[u] = cnt;
    top[u] = t;
    if ( son[u] ) DFS2(son[u], t); 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( v == fa[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline int read()
{
    char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    int x = 0;
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
    return x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { W[i] = read(); C[i] = read(); }
    REP(i, 1, n - 1) { int u = read(), v = read(); add(u, v); add(v, u); }
    DFS1(1); DFS2(1, 1);
    REP(i, 1, n) Update(Root[C[id[i]]], 1, n, i, W[id[i]]);
    char s[5];
    while ( m -- )
    {
        scanf("%s", s);
        int x = read(), y = read();
        if ( s[0] == 'C' && s[1] == 'C' ) 
        {
            Remove(Root[C[x]], 1, n, p[x]);
            C[x] = y;
            Update(Root[C[x]], 1, n, p[x], W[x]);
        }
        if ( s[0] == 'C' && s[1] == 'W' )
        {
            Remove(Root[C[x]], 1, n, p[x]);
            W[x] = y;
            Update(Root[C[x]], 1, n, p[x], W[x]);
        }
        if ( s[0] == 'Q' && s[1] == 'S' )
        {
            int u = x, v = y, ans = 0, k = C[x];
            while ( top[u] != top[v] ) 
            {
                if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
                ans += Query_sum(Root[k], 1, n, p[top[u]], p[u]);
                u = fa[top[u]];
            }
            if ( dis[u] > dis[v] ) swap(u, v);
            ans += Query_sum(Root[k], 1, n, p[u], p[v]);
            printf("%d\n", ans);
        }
        if ( s[0] == 'Q' && s[1] == 'M' )
        {
            int u = x, v = y, ans = 0, k = C[x];
            while ( top[u] != top[v] ) 
            {
                if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
                ans = max(ans, Query_Max(Root[k], 1, n, p[top[u]], p[u]));
                u = fa[top[u]];
            }
            if ( dis[u] > dis[v] ) swap(u, v);
            ans = max(ans, Query_Max(Root[k], 1, n, p[u], p[v]));
            printf("%d\n", ans);
        }
    }
    return 0;
}

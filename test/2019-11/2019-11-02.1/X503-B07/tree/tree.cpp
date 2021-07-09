/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 14时40分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 400010;

struct node { int sum, lazy, len; } Tree[maxn << 2];
int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], f[maxn];
int son[maxn], size[maxn], p[maxn], id[maxn], top[maxn], cnt, ans[maxn], N;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; dis[v] = dis[u] + 1;
        DFS1(v, u);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ cnt; p[cnt] = u; top[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root) 
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    Tree[lson].lazy += x; Tree[rson].lazy += x; 
    Tree[lson].sum += x * Tree[lson].len;
    Tree[rson].sum += x * Tree[rson].len;
}

inline void Modify(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        Tree[root].sum += Tree[root].len; ++ Tree[root].lazy;
        return ;
    }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    PushDown(root);
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(lson, l, Mid, L, R);
    if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R);
    return sum;
}

inline void Update(int x)
{
    while ( x ) { Modify(1, 1, n, id[top[x]], id[x]); x = f[top[x]]; }
}

inline int Solve(int x)
{
    int sum = 0;
    while ( x ) { sum += Query(1, 1, n, id[top[x]], id[x]); x = f[top[x]]; }
    return sum;
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    int sum = 0;
    REP(i, 1, n) { Update(i); sum += dis[i]; }
    REP(i, 1, n)
    {
        int ans = sum + n * dis[i];
        ans = ans - 2 * Solve(i);
        printf("%lld\n", ans);
    }
    return 0;
}


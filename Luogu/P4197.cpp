// luogu-judger-enable-o2
/***************************************************************
    File name: P4197.cpp
    Author: ljfcnyali
    Create time: 2019年07月10日 星期三 09时22分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 500010 * 20;

struct node
{
    int u, v, w;
    bool operator < (const node & a) const
    {
        return w < a.w;
    }
} edge[maxn];

struct node1
{
    int val, pos;
    bool operator < (const node1 & a) const
    {
        return val < a.val;
    }
} a[maxn];

struct tree
{
    int l, r, size;
} Tree[maxn];

int n, m, q, h[maxn], f[maxn], cnt, tot, sum, W[maxn], s;
int Root[maxn], num, L[maxn], R[maxn], p[maxn], id[maxn], pre[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, anc[maxn][20];

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    if ( u <= n ) { W[++ s] = h[u]; L[u] = R[u] = s; id[s] = u; pre[u] = s; }
    else L[u] = 0x3f3f3f3f;
    anc[u <= n ? s : u][0] = fa;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        DFS(v, u);
        L[u] = min(L[u], L[v]); R[u] = max(R[u], R[v]);
    }
}

inline void Push_up(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline int Build(int root, int l, int r)
{
    root = ++ num; ls(root) = rs(root) = Tree[root].size = 0; 
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    ls(root) = Build(ls(root), l, Mid); 
    rs(root) = Build(rs(root), Mid + 1, r);
    return root;
}

inline int Update(int now, int l, int r, int x)
{
    int root = ++ num; Tree[root] = Tree[now];
    ++ Tree[root].size;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( x <= Mid ) ls(root) = Update(ls(root), l, Mid, x);
    else rs(root) = Update(rs(root), Mid + 1, r, x);
    return root;
}

inline int Query(int p, int q, int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1, sum = Tree[rs(p)].size - Tree[rs(q)].size;
    if ( k <= sum ) return Query(rs(p), rs(q), Mid + 1, r, k);
    return Query(ls(p), ls(q), l, Mid, k - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].pos = i; } 
    sort(a + 1, a + n + 1);
    a[0].val = -0x3f3f3f3f;
    REP(i, 1, n) 
    {
        if ( a[i].val != a[i - 1].val ) ++ cnt;
        h[a[i].pos] = cnt;
    }
    REP(i, 1, m) scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    sort(edge + 1, edge + m + 1);
    REP(i, 1, n) f[i] = p[i] = i; tot = n;
    REP(i, 1, m)
    {
        int fx = cha(edge[i].u), fy = cha(edge[i].v);
        if ( fx != fy ) 
        {
            f[fx] = fy;
            W[++ tot] = edge[i].w;
            add(tot, p[fx]); add(tot, p[fy]);
            p[fy] = tot;
            ++ sum;
        }
        if ( sum == n - 1 ) break ; 
    }
    DFS(tot, 0);
    //REP(i, 1, tot) printf("%d %d %d %d %d\n", i, L[i], R[i], W[i], id[i]);
    Root[0] = Build(Root[0], 1, cnt);
    REP(i, 1, n) Root[i] = Update(Root[i - 1], 1, n, W[i]);
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( q -- ) 
    {
        int u, x, k; scanf("%d%d%d", &u, &x, &k);
        u = pre[u]; 
        //printf("%d ", u);
        for ( int j = 19; j >= 0; -- j ) 
            if ( anc[u][j] && W[anc[u][j]] <= x ) u = anc[u][j];
        if ( anc[u][0] && W[anc[u][0]] <= x ) u = anc[u][0];
        //printf("%d ", u);
        x = Query(Root[R[u]], Root[L[u] - 1], 1, cnt, k);
        int sum = Tree[Root[R[u]]].size - Tree[Root[L[u] - 1]].size;
        //printf("%d ", sum);
        if ( sum < k ) { printf("-1\n"); continue ; } 
        //printf("%d ", x);
        printf("%d\n", Query(Root[R[u]], Root[L[u] - 1], 1, cnt, k));
    }
    return 0;
}

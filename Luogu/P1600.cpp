/***************************************************************
	File name: P1600.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 16时01分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 6000010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, Root[maxn], w[maxn], cnt, tot, ans[maxn];
int dis[maxn], anc[maxn][25], in[maxn], out[maxn];

struct node
{
    int l, r, sum;
} Tree[maxn];

struct Node
{
    int u, v, lca;
} a[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    in[u] = ++ tot;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        anc[v][0] = u;
        DFS(v, u);
    }
    out[u] = tot;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 22; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 22; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void Update(int &root, int x, int l, int r, int val)
{
    if ( !x ) return ;
    if ( !root ) root = ++ cnt;
    Tree[root].sum += val;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( x <= Mid ) Update(ls(root), x, l, Mid, val);
    else Update(rs(root), x, Mid + 1, r, val);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) sum += Query(rs(root), Mid + 1, r, L, R);
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 22) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) scanf("%d", &w[i]);
    REP(i, 1, m) 
    { 
        scanf("%d%d", &a[i].u, &a[i].v); 
        a[i].lca = LCA(a[i].u, a[i].v); 
    }
    REP(i, 1, m)
    {
        int x = dis[a[i].u];
        Update(Root[x], in[a[i].u], 1, n, 1);
        Update(Root[x], in[anc[a[i].lca][0]], 1, n, -1);
//        cerr << Root[x] << endl;
    }
    REP(i, 1, n) ans[i] = Query(Root[dis[i] + w[i]], 1, n, in[i], out[i]);
//    REP(i, 1, n) cerr << ans[i] << " ";
    mem(Root); mem(Tree); cnt = 0;
    REP(i, 1, m)
    {
        int x = dis[a[i].u] - 2 * dis[a[i].lca] + 2 * n;
//        printf("%d %d %d\n", x, a[i].v, a[i].lca);
        Update(Root[x], in[a[i].v], 1, n, 1);
        Update(Root[x], in[a[i].lca], 1, n, -1);
    }
//    REP(i, 1, n) printf("%d\n", w[i] - dis[i] + 2 * n);
    REP(i, 1, n) ans[i] += Query(Root[w[i] - dis[i] + 2 * n], 1, n, in[i], out[i]);
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}

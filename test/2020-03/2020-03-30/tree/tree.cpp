#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, q, Begin[maxn], Next[maxn], To[maxn], e, Root[maxn];
int size[maxn], dfn[maxn], id[maxn], tot, cnt, dis[maxn], N;
struct node
{
    int l, r, sum;
} Tree[maxn << 5];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    dfn[u] = ++ cnt; id[cnt] = u; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; N = max(N, dis[v]); DFS(v, u);
        size[u] += size[v];
    }
}

inline int Modify(int now, int l, int r, int pos, int val)
{
    int root = ++ tot; Tree[root] = Tree[now];
    Tree[root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos, val);
    else rs(root) = Modify(rs(root), Mid + 1, r, pos, val);
    return root;
}

inline int Query(int p, int q, int l, int r, int L, int R)
{
    if ( !q || Tree[q].sum - Tree[p].sum == 0 ) return 0;
    if ( L <= l && r <= R ) return Tree[q].sum - Tree[p].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(ls(p), ls(q), l, Mid, L, R);
    if ( Mid < R ) sum += Query(rs(p), rs(q), Mid + 1, r, L, R);
    return sum;
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(i, 1, n) Root[i] = Modify(Root[i - 1], 1, N, dis[id[i]], size[id[i]] - 1);
    REP(i, 1, q)
    {
        int p, k, x; scanf("%lld%lld", &p, &k);
        if ( dis[p] - 1 <= k ) x = dis[p] - 1;
        else x = k;
        int ans = x * (size[p] - 1);
        ans += Query(Root[dfn[p]], Root[dfn[p] + size[p] - 1], 1, N, min(N, dis[p] + 1), min(N, dis[p] + k));
        printf("%lld\n", ans);
    }
    return 0;
}

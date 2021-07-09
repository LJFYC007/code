/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2020年05月31日 星期日 19时29分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], Root[maxn], tot, dep[maxn];
struct node { int lson, rson, Max; } Tree[maxn << 5];

inline void PushUp(int root) { Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max); }

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = ++ tot;
    if ( l == r ) { Tree[root].Max = max(Tree[p].Max, Tree[q].Max); return root; } 
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(p), ls(q), l, Mid); rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(root); return root;
}

inline int Modify(int now, int l, int r, int pos, int val)
{
    if ( val <= Tree[now].Max ) return now;
    int root = ++ tot; Tree[root] = Tree[now]; Tree[root].Max = val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos, val);
    else rs(root) = Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root); return root;
}

inline int Query(int root, int l, int r, int k)
{
    if ( Tree[root].Max < k ) return -1;
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    int x = Query(ls(root), l, Mid, k);
    if ( x != -1 ) return x;
    return Query(rs(root), Mid + 1, r, k);
}

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    Root[u] = Modify(Root[u], 1, n, dep[u], dis[u]);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + W[i]; dep[v] = dep[u] + 1; DFS(v, u);
        Root[u] = Merge(Root[u], Root[v], 1, n);
    }
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d", &m, &n); 
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    dep[1] = 1; DFS(1, 0);
    scanf("%d", &m);
    while ( m -- ) 
    {
        int x, k; scanf("%d%d", &x, &k);
        int ans = Query(Root[x], 1, n, k + dis[x]);
        if ( ans != -1 ) ans -= dep[x];
        printf("%d\n", ans);
    }
    return 0;
}

/***************************************************************
	File name: journey.cpp
	Author: ljfcnyali
	Create time: 2020年11月21日 星期六 09时20分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int N = 2e9;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn];
int ans[maxn], a[maxn], b[maxn], Root[maxn], tot, id[maxn];
struct node { int lson, rson; pii x; } Tree[maxn * 5];

inline int f(pii x, int pos) { return x.first + x.second * pos; }

inline void Modify(int &root, int l, int r, pii x)
{
    if ( !root ) { root = ++ tot; Tree[root].x = x; return ; }
    int Mid = (l + r) >> 1;
    if ( f(Tree[root].x, Mid) < f(x, Mid) ) swap(Tree[root].x, x);
    if ( x.second < Tree[root].x.second ) Modify(ls(root), l, Mid, x);
    else if ( x.second > Tree[root].x.second ) Modify(rs(root), Mid + 1, r, x);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( !root ) return 0;
    if ( l == r ) return f(Tree[root].x, pos);
    int Mid = l + r >> 1, ret = f(Tree[root].x, pos);
    if ( pos <= Mid ) ret = max(ret, Query(ls(root), l, Mid, pos));
    else ret = max(ret, Query(rs(root), Mid + 1, r, pos));
    return ret;
}

inline void Merge(int &p, int q, int l, int r)
{
    if ( !p || !q ) { p = p + q; return ; }
    pii x; int Mid = l + r >> 1;
    if ( f(Tree[p].x, Mid) < f(Tree[q].x, Mid) ) swap(Tree[p].x, Tree[q].x);
    if ( l == r ) return ;
    Merge(ls(p), ls(q), l, Mid); Merge(rs(p), rs(q), Mid + 1, r);
    Modify(p, l, r, Tree[q].x);
}

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    id[u] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + W[i]; DFS(v, u);
        Merge(Root[u], Root[v], 0, N);
    }
    ans[u] = Query(Root[id[u]], 0, N, a[u] + dis[u]);
    pii x = pii(ans[u] - dis[u] * b[u], b[u]);
    Modify(Root[id[u]], 0, N, x); 
}

signed main()
{
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
    scanf("%lld", &n); 
    REP(i, 1, n) scanf("%lld%lld", &a[i], &b[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(1, 0);
    REP(i, 1, n) printf("%lld\n", ans[i]);
    return 0;
}

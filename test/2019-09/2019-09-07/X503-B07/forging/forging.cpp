/***************************************************************
	File name: forging.cpp
	Author: ljfcnyali
	Create time: 2019年09月07日 星期六 09时35分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 4000010;
const int maxm = 200010;

struct node
{
    int lson, rson, size, sum;
} Tree[maxn];
int n, Begin[maxm], Next[maxm], To[maxm], e, W[maxm];
int dis[maxm], q, Root[maxm], num = 100000000, tot, cnt;
int size[maxm], dfn[maxm], p[maxm];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int Modify(int now, int l, int r, int val)
{
    int root = ++ tot; Tree[root] = Tree[now];
    ++ Tree[root].size; Tree[root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( val <= Mid ) ls(root) = Modify(ls(root), l, Mid, val);
    else rs(root) = Modify(rs(root), Mid + 1, r, val);
    return root;
}

inline int Query(int p, int q, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[p].sum - Tree[q].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(ls(p), ls(q), l, Mid, L, R);
    if ( Mid < R ) sum += Query(rs(p), rs(q), Mid + 1, r, L, R);
    return sum;
}

inline int Query_size(int p, int q, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[p].size - Tree[q].size;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query_size(ls(p), ls(q), l, Mid, L, R);
    if ( Mid < R ) sum += Query_size(rs(p), rs(q), Mid + 1, r, L, R);
    return sum;
}

inline void DFS(int u)
{
    dfn[u] = ++ cnt; p[cnt] = u; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        dis[v] = dis[u] + W[i];
        DFS(v);
        size[u] += size[v];
    }
}

signed main()
{
    freopen("forging.in", "r", stdin);
    freopen("forging.out", "w", stdout);
    scanf("%lld", &n);    
    REP(i, 2, n) { int fa, w; scanf("%lld%lld", &fa, &w); add(fa, i, w); }
    DFS(1);
    REP(i, 1, n) Root[i] = Modify(Root[i - 1], 1, num, dis[p[i]]);
    scanf("%lld", &q);
    while ( q -- ) 
    {
        int u, val; scanf("%lld%lld", &u, &val); val += dis[u];
        int sum = Query(Root[dfn[u] + size[u] - 1], Root[dfn[u] - 1], 1, num, val, num);
        int s = Query_size(Root[dfn[u] + size[u] - 1], Root[dfn[u] - 1], 1, num, val, num);
        printf("%lld\n", sum - dis[u] * s);
    }
    return 0;
}

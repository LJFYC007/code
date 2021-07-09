/***************************************************************
	File name: P2633.cpp
	Author: ljfcnyali
	Create time: 2019年07月14日 星期日 20时13分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 200010;

int n, m, h[maxn], ans, Root[maxn], cnt, num, dis[maxn];
int anc[maxn][20], Begin[maxn], Next[maxn], To[maxn], e, id[maxn];

struct node
{
    int l, r, size;
} Tree[maxn << 5];

struct Node
{
    int val, opt;
    bool operator < (const Node &a) const { return val < a.val; }
} a[maxn];

inline int Update(int now, int l, int r, int val)
{
    int root = ++ cnt; Tree[root] = Tree[now];
    ++ Tree[root].size;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( val <= Mid ) ls(root) = Update(ls(root), l, Mid, val);
    else rs(root) = Update(rs(root), Mid + 1, r, val);
    return root;
}

inline int Query(int p1, int p2, int q1, int q2, int l, int r, int k)
{
    if ( l == r ) return id[l];
    int Mid = l + r >> 1;
    int sum = Tree[ls(p1)].size + Tree[ls(p2)].size - Tree[ls(q1)].size - Tree[ls(q2)].size;
    if ( k <= sum ) return Query(ls(p1), ls(p2), ls(q1), ls(q2), l, Mid, k);
    else return Query(rs(p1), rs(p2), rs(q1), rs(q2), Mid + 1, r, k - sum);
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        Root[v] = Update(Root[u], 1, num, h[v]);
        anc[v][0] = u;
        DFS(v, u);
    }
}

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 16; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 16; j >= 0; -- j ) 
        if ( anc[x][j] != anc[y][j] )
        {
            x = anc[x][j]; y = anc[y][j];
        }
    return anc[x][0];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].opt = i; }
    sort(a + 1, a + n + 1);
    a[0].val = -1;
    REP(i, 1, n) 
    {
        if ( a[i].val != a[i - 1].val ) ++ num;
        h[a[i].opt] = num; id[num] = a[i].val;
    }
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    Root[1] = Update(Root[1], 1, num, h[1]);
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 16) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        int u, v, k; scanf("%d%d%d", &u, &v, &k); u ^= ans;
        int fa = LCA(u, v);
        ans = Query(Root[u], Root[v], Root[fa], Root[anc[fa][0]], 1, num, k);
        printf("%d\n", ans);
    }
    return 0;
}

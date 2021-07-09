/***************************************************************
	File name: P3302.cpp
	Author: ljfcnyali
	Create time: 2019年07月16日 星期二 14时39分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 320010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, q, h[maxn], id[maxn], num, cnt;
int dis[maxn], anc[maxn][20], Root[maxn], ans;
int size[maxn], f[maxn];

struct node
{
    int l, r, size;
} Tree[maxn << 5];

struct Node
{
    int val, pos;
    bool operator < (const Node &a) const { return val < a.val; }
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

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

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        Root[v] = Update(Root[u], 1, num, h[v]);
        DFS(v, u);
    }
}

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline int Query(int p1, int p2, int q1, int q2, int l, int r, int k)
{
    if ( l == r ) return id[l];
    int Mid = l + r >> 1, sum = 0;
    sum = Tree[ls(p1)].size + Tree[ls(p2)].size - Tree[ls(q1)].size - Tree[ls(q2)].size;
    if ( k <= sum ) return Query(ls(p1), ls(p2), ls(q1), ls(q2), l, Mid, k);
    else return Query(rs(p1), rs(p2), rs(q1), rs(q2), Mid + 1, r, k - sum);
}

inline void DFS1(int u, int fa)
{
    REP(j, 1, 18) anc[u][j] = anc[anc[u][j - 1]][j - 1];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        Root[v] = Update(Root[u], 1, num, h[v]);
        DFS1(v, u);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &q);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].pos = i; }
    sort(a + 1, a + n + 1); a[0].val = -1;
    REP(i, 1, n) 
    {
        if ( a[i].val != a[i - 1].val ) ++ num;
        h[a[i].pos] = num; id[num] = a[i].val;
    }
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m) 
    { 
        int u, v; scanf("%d%d", &u, &v); 
        add(u, v); add(v, u); 
        int fx = cha(u), fy = cha(v);
        if ( fx == fy ) continue ;
        if ( size[fx] == size[fy] ) ++ size[fx]; if ( size[fx] < size[fy] ) swap(fx, fy);
        f[fy] = fx;
    }
    REP(i, 1, n) if ( !dis[i] ) { Root[i] = Update(Root[i], 1, num, h[i]); dis[i] = 1; DFS(i, 0); }
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( q -- )
    {
        getchar();
        getchar(); char c = getchar();
        if ( c == 'Q' ) 
        {
            int u, v, k; scanf("%d%d%d", &u, &v, &k);
            u ^= ans; v ^= ans; k ^= ans;
            int x = LCA(u, v), y = anc[x][0];
            //cerr << u << " " << v << " " << x << " " << y << endl;
            //cerr << Tree[Root[u]].size << " " << Tree[Root[v]].size << endl;
            ans = Query(Root[u], Root[v], Root[x], Root[y], 1, num, k);
            printf("%d\n", ans);
        }
        else
        {
            int u, v; scanf("%d%d", &u, &v);
            u ^= ans; v ^= ans;
            int fx = cha(u), fy = cha(v);
            if ( fx == fy ) continue ;
            if ( size[fx] == size[fy] ) ++ size[fx];
            if ( size[fx] < size[fy] ) { swap(fx, fy); swap(u, v); }
            f[fy] = fx; add(v, u); add(u, v); anc[v][0] = u; dis[v] = dis[u] + 1;
            Root[v] = Update(Root[u], 1, num, h[v]);
            DFS1(v, u);
        }
    }
    return 0;
}

/***************************************************************
	File name: P4556.cpp
	Author: ljfcnyali
	Create time: 2019年09月16日 星期一 19时36分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 200010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], anc[maxn][20], Root[maxn], tot, N = 100000, ans[maxn];
struct node
{
    int lson, rson, Max, x;
} Tree[maxn << 5];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v][0] = u; dis[v] = dis[u] + 1;
        DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void PushUp(int root)
{
    if ( Tree[ls(root)].Max >= Tree[rs(root)].Max ) Tree[root].Max = Tree[ls(root)].Max, Tree[root].x = Tree[ls(root)].x;
    else Tree[root].Max = Tree[rs(root)].Max, Tree[root].x = Tree[rs(root)].x;
}

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) { Tree[root].Max += val; if ( Tree[root].Max > 0 ) Tree[root].x = l;  else Tree[root].x = 0; return ; }
    int Mid = (l + r) >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    if ( l == r ) { Tree[p].Max += Tree[q].Max; Tree[p].x = l; return p; }
    int Mid = (l + r) >> 1;
    ls(p) = Merge(ls(p), ls(q), l, Mid); 
    rs(p) = Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(p);
    return p;
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS2(v, u);
        Root[u] = Merge(Root[u], Root[v], 1, N);
    }
    ans[u] = Tree[Root[u]].Max > 0 ? Tree[Root[u]].x : 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);    
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0);
    REP(i, 1, n) REP(j, 1, 18) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        Modify(Root[u], 1, N, w, 1);
        Modify(Root[v], 1, N, w, 1);
        int Lca = LCA(u, v);
        Modify(Root[Lca], 1, N, w, -1);
        Modify(Root[anc[Lca][0]], 1, N, w, -1);
    }
    DFS2(1, 0);
    REP(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}

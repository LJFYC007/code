/***************************************************************
	File name: noname.cpp
	Author: ljfcnyali
	Create time: 2020年09月29日 星期二 11时24分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, c[maxn], dis[maxn], anc[maxn][20], tot;
int Begin[maxn], Next[maxn], To[maxn], e, Root[maxn], ans;
pii Ans;
struct node { int lson, rson, len; pii x; } Tree[maxn << 5];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS1(v, u);
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

inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline void PushUp(int root)
{
    if ( Tree[ls(root)].len > Tree[rs(root)].len ) { Tree[root].len = Tree[ls(root)].len; Tree[root].x = Tree[ls(root)].x; }
    else { Tree[root].len = Tree[rs(root)].len; Tree[root].x = Tree[rs(root)].x; }
    if ( Tree[ls(root)].len != -1 && Tree[rs(root)].len != -1 ) 
    {
        int x, A = Tree[ls(root)].x.x, B = Tree[ls(root)].x.y, C = Tree[rs(root)].x.x, D = Tree[rs(root)].x.y;
        x = Dis(A, C); if ( x > Tree[root].len ) { Tree[root].len = x; Tree[root].x = pii(A, C); }
        x = Dis(A, D); if ( x > Tree[root].len ) { Tree[root].len = x; Tree[root].x = pii(A, D); }
        x = Dis(B, C); if ( x > Tree[root].len ) { Tree[root].len = x; Tree[root].x = pii(B, C); }
        x = Dis(B, D); if ( x > Tree[root].len ) { Tree[root].len = x; Tree[root].x = pii(B, D); }
    }
}

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot; 
    if ( l == r ) { Tree[root].len = val; Tree[root].x = pii(l, l); return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Build(int &root, int l, int r)
{
    root = ++ tot;
    if ( l == r ) { Tree[root].len = Tree[Root[l]].len; Tree[root].x = Tree[Root[l]].x; return ; }
    int Mid = l + r >> 1; Build(ls(root), l, Mid); Build(rs(root), Mid + 1, r);
    PushUp(root);
}

inline void Modify1(int root, int l, int r, int pos, pii x)
{
    if ( l == r ) 
    { 
        Modify(Root[l], 1, n, x.first, x.second);
        Tree[root].len = Tree[Root[l]].len; Tree[root].x = Tree[Root[l]].x; 
        return ; 
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify1(ls(root), l, Mid, pos, x);
    else Modify1(rs(root), Mid + 1, r, pos, x);
    PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        if ( Tree[root].len != -1 && ans != -1 ) 
        {
            int x, A = Ans.x, B = Ans.y, C = Tree[root].x.x, D = Tree[root].x.y;
            x = Dis(A, C); if ( x > ans ) { ans = x; Ans = pii(A, C); }
            x = Dis(A, D); if ( x > ans ) { ans = x; Ans = pii(A, D); }
            x = Dis(B, C); if ( x > ans ) { ans = x; Ans = pii(B, C); }
            x = Dis(B, D); if ( x > ans ) { ans = x; Ans = pii(B, D); }
        }
        if ( Tree[root].len > ans ) { ans = Tree[root].len; Ans = Tree[root].x; }
        return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) Query(rs(root), Mid + 1, r, L, R);
}

int main()
{
    freopen("noname.in", "r", stdin);
    freopen("noname.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    Tree[0].len = -1;
    REP(i, 1, n) Modify(Root[c[i]], 1, n, i, 0);
    Build(Root[0], 1, m);
    while ( q -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            Modify1(Root[0], 1, m, c[l], pii(l, -1));
            c[l] = r;
            Modify1(Root[0], 1, m, c[l], pii(l, 0));
        }
        else 
        {
            ans = -1; Query(Root[0], 1, m, l, r);
            printf("%d\n", max(ans, 0));
        }
    }
    return 0;
}

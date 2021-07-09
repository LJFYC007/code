/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 07时58分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], ans[maxn], Max;
int p[maxn], fa[maxn], son[maxn], top[maxn];
vector<int> P[maxn];
struct node 
{ 
    int A, B, len, fa, size; 
    node ( int a = 0, int b = 0, int c = 0, int d = 0, int e = 0 ) { A = a; B = b; len = c; fa = d; size = e; }
} a[maxn];
struct node1
{
    vector<pii> Q;
    vector< pair<node, int> > A;
} Tree[maxn << 2];

inline int find(int x) { return x == a[x].fa ? x : find(a[x].fa); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int pre)
{
    p[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == pre ) continue ;
        dis[v] = dis[u] + 1; fa[v] = u; 
        DFS1(v, u);
        p[u] += p[v];
        if ( p[v] > Max ) { Max = p[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) 
    {
        if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
        x = fa[top[x]];
    }
    return dis[x] < dis[y] ? x : y;
}


inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline void Build(int root, int l, int r, int L, int R, pii x)
{
    if ( L <= l && r <= R ) { Tree[root].Q.push_back(x); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Build(lson, l, Mid, L, R, x);
    if ( Mid < R ) Build(rson, Mid + 1, r, L, R, x);
}

inline void Merge(int x, int y)
{
    a[x].fa = y; a[y].size += a[x].size;
    int A1 = a[x].A, B1 = a[y].A, dis1 = Dis(A1, B1); 
    int A2 = a[x].A, B2 = a[y].B, dis2 = Dis(A2, B2); 
    int A3 = a[x].B, B3 = a[y].A, dis3 = Dis(A3, B3); 
    int A4 = a[x].B, B4 = a[y].B, dis4 = Dis(A4, B4); 
    int A5 = a[x].A, B5 = a[x].B, dis5 = a[x].len;
    if ( dis1 > a[y].len ) { a[y].len = dis1; a[y].A = A1; a[y].B = B1; }
    if ( dis2 > a[y].len ) { a[y].len = dis2; a[y].A = A2; a[y].B = B2; }
    if ( dis3 > a[y].len ) { a[y].len = dis3; a[y].A = A3; a[y].B = B3; }
    if ( dis4 > a[y].len ) { a[y].len = dis4; a[y].A = A4; a[y].B = B4; }
    if ( dis5 > a[y].len ) { a[y].len = dis5; a[y].A = A5; a[y].B = B5; }
    Max = max(Max, a[y].len);
}

inline void Solve(int root, int l, int r)
{
    int x = Max;
    for ( auto i : Tree[root].Q ) 
    {
        int x = find(i.first), y = find(i.second);
        if ( x != y ) 
        {
            Tree[root].A.push_back(make_pair(a[x], x));
            Tree[root].A.push_back(make_pair(a[y], y));
            if ( a[x].size > a[y].size ) swap(x, y);
            Merge(x, y);
        }
    }
    if ( l == r ) 
    {
        for ( auto i : P[l] ) ans[i] = Max; 
        Max = x;
        for ( int i = (int)(Tree[root].A.size()) - 1; i >= 0; -- i ) 
            a[Tree[root].A[i].second] = Tree[root].A[i].first;
        return ;
    }
    int Mid = l + r >> 1;
    Solve(lson, l, Mid); Solve(rson, Mid + 1, r);
    Max = x;
    for ( int i = (int)(Tree[root].A.size()) - 1; i >= 0; -- i ) 
        a[Tree[root].A[i].second] = Tree[root].A[i].first;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) 
    { 
        int u, v, l, r; read(u); read(v); read(l); read(r);
        add(u, v); add(v, u); Build(1, 1, n, l, r, pii(u, v));
    }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    REP(i, 1, n) { a[i].fa = i; a[i].A = a[i].B = i; a[i].size = 1; }
    REP(i, 1, m)
    {
        int v; read(v);
        P[v].push_back(i);
    }
    Solve(1, 1, n);
    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}

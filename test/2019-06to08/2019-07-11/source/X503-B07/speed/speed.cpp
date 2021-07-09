/***************************************************************
	File name: speed.cpp
	Author: ljfcnyali
	Create time: 2019年07月11日 星期四 10时32分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define swap sswap

const int maxn = 500010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, ans[maxn], dis[maxn], son[maxn], p[maxn], fa[maxn], top[maxn];
int f[maxn], A[maxn], B[maxn], tot, size[maxn];
vector<int> Edge[maxn][2];

struct node
{
    int pos, x, y;
    node(){};
    node(int Pos, int X, int Y) { pos = Pos; x = X; y = Y; }
} Stack[maxn];

inline void read(int &x) 
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void sswap(int &x, int &y) { int t = x; x = y; y = t; }
 
inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

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

inline int cha(int x) { return x == f[x] ? x : cha(f[x]); }

inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline void Build(int root, int l, int r, int L, int R, int u, int v)
{
    if ( L <= l && r <= R ) 
    {
        Edge[root][0].push_back(u); Edge[root][1].push_back(v);
        return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Build(lson, l, Mid, L, R, u, v);
    if ( Mid < R ) Build(rson, Mid + 1, r, L, R, u, v);
}

inline void Merge(int x, int y, int &num)
{
    x = cha(x); y = cha(y);
    int t = -1, u, v, sum;
    sum = Dis(A[x], B[x]); 
    if ( sum > t ) { t = sum; u = A[x]; v = B[x]; }
    sum = Dis(A[x], A[y]); 
    if ( sum > t ) { t = sum; u = A[x]; v = A[y]; }
    sum = Dis(A[x], B[y]); 
    if ( sum > t ) { t = sum; u = A[x]; v = B[y]; }
    sum = Dis(B[x], A[y]); 
    if ( sum > t ) { t = sum; u = B[x]; v = A[y]; }
    sum = Dis(B[x], B[y]); 
    if ( sum > t ) { t = sum; u = B[x]; v = B[y]; }
    sum = Dis(A[y], B[y]); 
    if ( sum > t ) { t = sum; u = A[y]; v = B[y]; }
    num = max(num, t);
    if ( size[x] == size[y] ) { ++ size[x]; Stack[++ tot] = node(0, x, 0); } 
    if ( size[x] < size[y] ) swap(x, y);
    Stack[++ tot] = node(1, y, 0);
    Stack[++ tot] = node(2, x, A[x]);
    Stack[++ tot] = node(3, x, B[x]);
    f[y] = x; A[x] = u; B[x] = v;
}

inline void Return(int t)
{
    while ( tot > t ) 
    {
        if ( Stack[tot].pos == 0 ) -- size[Stack[tot].x];
        if ( Stack[tot].pos == 1 ) f[Stack[tot].x] = Stack[tot].x;
        if ( Stack[tot].pos == 2 ) A[Stack[tot].x] = Stack[tot].y;
        if ( Stack[tot].pos == 3 ) B[Stack[tot].x] = Stack[tot].y;
        -- tot;
    }
}

inline void Solve(int root, int l, int r, int num)
{
    int pos = tot, _end_ = Edge[root][0].size() - 1, i;
    for ( i = 0; i <= _end_; i += 2 ) 
    REP(i, 0, Edge[root][0].size() - 1)
        Merge(Edge[root][0][i], Edge[root][1][i], num);
    if ( l == r ) 
    {
        ans[l] = num; Return(pos); 
        return ;
    }
    int Mid = l + r >> 1;
    Solve(lson, l, Mid, num); Solve(rson, Mid + 1, r, num);
    Return(pos);
}

int main()
{
    read(n); read(m);
    REP(i, 1, n - 1) 
    {
        int u, v, l, r; read(u); read(v); read(l); read(r);
        add(u, v); add(v, u);
        Build(1, 1, n, l, r, u, v);
    }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    REP(i, 1, n) f[i] = A[i] = B[i] = i;
    Solve(1, 1, n, 0);
    REP(i, 1, m) { int x; read(x); printf("%d\n", ans[x]); }
    return 0;
}

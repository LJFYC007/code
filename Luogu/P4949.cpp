/***************************************************************
	File name: P4949.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 18时15分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], d[maxn];
int size[maxn], top[maxn], son[maxn], dis[maxn], a[maxn];
int f[maxn], id[maxn], p[maxn], Root[maxn], cnt, N;
bool use[maxn], vis[maxn];
vector<int> circle, num; 

struct NODE { int u, v, w; } Edge[maxn];
struct node { int sum; } Tree[2][maxn << 2];

inline void PushUp(int root, int opt) { Tree[opt][root].sum = Tree[opt][lson].sum + Tree[opt][rson].sum; }

inline void Build(int root, int l, int r, int opt)
{
    if ( l == r ) { Tree[opt][root].sum = !opt ? a[p[l]] : num[l]; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid, opt); Build(rson, Mid + 1, r, opt);
    PushUp(root, opt);
}

inline void Modify(int root, int l, int r, int pos, int val, int opt)
{
    if ( l == r ) { Tree[opt][root].sum = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, opt);
    else Modify(rson, Mid + 1, r, pos, val, opt);
    PushUp(root, opt);
}

inline int Query(int root, int l, int r, int L, int R, int opt)
{
    if ( L > R ) return 0;
    if ( L <= l && r <= R ) return Tree[opt][root].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(lson, l, Mid, L, R, opt);
    if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R, opt);
    return sum;
}

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] || use[v] ) continue ;
        vis[v] = true; circle.push_back(v); id[v] = circle.size() - 1;
        DFS(v);
    }
}

inline void toposort()
{
    queue<int> Q;
    REP(i, 1, n) if ( d[i] == 1 ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); use[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 1 ) Q.push(v);
        }
    }
    REP(i, 1, n) if ( !use[i] ) { circle.push_back(i); vis[i] = true; DFS(i); break ; }
}

inline void DFS1(int u, int fa, int x)
{
    Root[u] = x; size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; f[v] = u; a[v] = W[i];
        DFS1(v, u, x);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ cnt; p[cnt] = u; top[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline int Solve(int u, int v, int x)
{
    int sum = 0;
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] <= dis[top[v]] ) swap(u, v);
        sum += Query(1, 1, n, id[top[u]], id[u], 0);
        u = f[top[u]];
    }
    if ( dis[u] > dis[v] ) swap(u, v);
    sum += Query(1, 1, n, id[u] + x, id[v], 0);
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    { 
        scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w); 
        add(Edge[i].u, Edge[i].v, Edge[i].w); add(Edge[i].v, Edge[i].u, Edge[i].w);
        ++ d[Edge[i].u]; ++ d[Edge[i].v];
    }
    toposort();
    // for ( auto i : circle ) printf("%d ", i); puts("");
    REP(j, 0, circle.size() - 1)
    {
        int u = circle[j]; id[u] = j;
        int suf = circle[j == circle.size() - 1 ? 0 : j + 1];
        // printf("%d %d\n", u, suf);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( use[v] ) 
            {
                dis[v] = 1; f[v] = u; a[v] = W[i]; DFS1(v, u, v); DFS2(v, v);
                continue ;
            }
            if ( v == suf ) num.push_back(W[i]);
        }
    }
    N = num.size() - 1;
    // for ( auto i : num ) printf("%d ", i); puts("");
    Build(1, 1, n, 0); Build(1, 0, N, 1);
    while ( m -- )
    {
        int opt, x, y; scanf("%d%d%d", &opt, &x, &y);
        if ( opt == 1 ) 
        {
            int u = Edge[x].u, v = Edge[x].v;
            if ( !use[u] && !use[v] ) 
            {
                if ( circle[id[u] == circle.size() - 1 ? 0 : id[u] + 1] != v ) swap(u, v);
                Modify(1, 0, N, id[u], y, 1);
                continue ;
            }
            if ( dis[u] > dis[v] ) swap(u, v);
            Modify(1, 1, n, id[v], y, 0);
            continue ;
        }
        if ( use[x] && use[y] && Root[x] == Root[y] ) { printf("%d\n", Solve(x, y, 1)); continue ; }
        int sum = 0;
        if ( use[x] ) { sum += Solve(x, Root[x], 0); x = f[Root[x]]; }
        if ( use[y] ) { sum += Solve(y, Root[y], 0); y = f[Root[y]]; }
        int L = id[x], R = id[y]; if ( L > R ) swap(L, R); 
        int sum1 = Query(1, 0, N, L, R - 1, 1);
        int sum2 = Query(1, 0, N, 0, L - 1, 1) + Query(1, 0, N, R, N, 1);
        sum += min(sum1, sum2);
        printf("%d\n", sum);
        // return 0;
    }
    return 0;
}

/***************************************************************
	File name: dierti.cpp
	Author: ljfcnyali
	Create time: 2020年11月27日 星期五 08时42分37秒
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

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, Root, fa[maxn], K;
LL sum, ans = 1;
int size[maxn], dis[maxn], tot, son[maxn], top[maxn], f[maxn], dfn[maxn], id[maxn];
struct node { int sum, Max, lazy; } Tree[maxn << 2];
bool vis[maxn], p[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int x)
{
    dis[u] = ++ x; size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] || f[u] == v ) continue ;
        f[v] = u; DFS1(v, x);
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    dfn[u] = ++ tot; id[tot] = u; top[u] = t;
    if ( !son[u] ) return ;
    DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void PushTag(int root, int val) { Tree[root].lazy += val; Tree[root].Max += val; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy);
    PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify2(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, val);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void Modify3(int root, int l, int r, int pos)
{
    ++ Tree[root].sum; if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify3(lson, l, Mid, pos);
    else Modify3(rson, Mid + 1, r, pos);
}

inline int Query2(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].Max;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query2(lson, l, Mid, pos);
    return Query2(rson, Mid + 1, r, pos);
}

inline int Query3(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; 
    if ( L <= Mid ) ret += Query3(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query3(rson, Mid + 1, r, L, R);
    return ret;
}

inline int Find(int root, int l, int r, int L, int R)
{
    if ( Tree[root].Max == 0 ) return L - 1;
    if ( l == r ) return l;
    int Mid = l + r >> 1; PushDown(root);
    if ( Mid < R && Tree[rson].Max > 0 ) return Find(rson, Mid + 1, r, L, R);
    return Find(lson, l, Mid, L, R);
}

inline bool Check(int x) 
{ 
    if ( vis[x] ) return false;
    int son = 0;
    for ( int i = Begin[x]; i; i = Next[i] ) if ( Query2(1, 1, n, dfn[To[i]]) ) 
    {
        ++ son;
        if ( son >= 2 ) break ; 
    }
    if ( son >= 2 ) vis[x] = true;
    return son == 1;
}

inline void Solve(int x)
{
    while ( top[x] ) 
    {
        int y = id[Find(1, 1, n, dfn[top[x]], dfn[x])];
        if ( y < top[x] ) x = f[top[x]];
        else { x = y; break ; }
    }

    if ( x < K ) { if ( !p[x] ) { p[x] = true; Modify3(1, 1, n, dfn[x]); } return ; }
    if ( Check(x) ) 
    { 
        sum += Query2(1, 1, n, dfn[x]); vis[x] = true; 
        if ( !p[x] ) { p[x] = true; Modify3(1, 1, n, dfn[x]); }
    }
}

inline void Modify1(int x) { while ( top[x] ) { Modify2(1, 1, n, dfn[top[x]], dfn[x], 1); x = f[top[x]]; } }

inline void Query1(int x) { while ( top[x] ) { sum += Query3(1, 1, n, dfn[top[x]], dfn[x]); x = f[top[x]]; } }

signed main()
{
    freopen("dierti.in", "r", stdin);
    freopen("dierti.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &fa[i]); if ( fa[i] ) add(fa[i], i); else Root = i; }
    dis[Root] = 1; DFS1(Root, 0); DFS2(Root, Root); p[0] = true;
    REP(i, 1, n)
    {
        K = i; int t = Query2(1, 1, n, dfn[i]);
        if ( t && Check(i) ) { sum += t; if ( !p[i] ) { p[i] = true; Modify3(1, 1, n, dfn[i]); } }
        else if ( !t ) Solve(fa[i]);
        ++ sum; Query1(fa[i]); Modify1(i);
        ans = ans * sum % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

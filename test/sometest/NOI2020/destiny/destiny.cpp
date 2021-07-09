/***************************************************************
	File name: destiny.cpp
	Author: ljfcnyali
	Create time: 2020年08月31日 星期一 20时52分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], dis[maxn];
int Root[maxn], tot, Rub[maxn << 4], top;
struct node { int lson, rson, val, lazya, lazyb; bool tag; } Tree[maxn << 4];

inline void NewNode(int &root) 
{ 
    if ( top ) { root = Rub[top --]; ls(root) = rs(root) = Tree[root].val = 0; }
    else root = ++ tot; 
    Tree[root].lazya = 1; Tree[root].lazyb = 0; Tree[root].tag = true; 
} 

inline void PushUp(int root)
{
    if ( !ls(root) || !rs(root) ) Tree[root].tag = true;
    else Tree[root].tag = (Tree[ls(root)].val == Tree[rs(root)].val) & Tree[ls(root)].tag & Tree[rs(root)].tag;
}

inline void PushTag(int root, pii x)
{
    Tree[root].lazya = Tree[root].lazya * x.first % Mod;
    Tree[root].lazyb = (Tree[root].lazyb * x.first + x.second) % Mod;
    Tree[root].val = (Tree[root].val * x.first + x.second) % Mod;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazya == 1 && Tree[root].lazyb == 0 ) return ; 
    if ( !ls(root) ) NewNode(ls(root)); PushTag(ls(root), pii(Tree[root].lazya, Tree[root].lazyb));
    if ( !rs(root) ) NewNode(rs(root)); PushTag(rs(root), pii(Tree[root].lazya, Tree[root].lazyb));
    Tree[root].lazya = 1; Tree[root].lazyb = 0;
}

inline void Modify(int &root, int l, int r, int L, int R)
{
    if ( L > R ) return ; if ( !root ) NewNode(root);
    Tree[root].tag = false;
    if ( L <= l && r <= R ) { Tree[root].tag = true; PushTag(root, pii(1, 1)); return ; }
    int Mid = l + r >> 1; 
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R); 
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( !root ) return 0;
    if ( l == r ) return Tree[root].val;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
    return Query(rs(root), Mid + 1, r, pos);
}

inline void Merge(int &p, int q, int l, int r, int x)
{
    if ( !p ) return ;
    if ( !q ) { PushTag(p, pii(x, 0)); return ; }
    if ( Tree[p].tag ) 
    {
        PushTag(q, pii(Tree[p].val, Tree[p].val * x % Mod));
        Rub[++ top] = p; p = q; return ; 
    }
    if ( Tree[q].tag ) 
    {
        PushTag(p, pii(Tree[q].val + x, 0));
        Rub[++ top] = q; return ;
    }
    if ( l == r ) { Tree[p].val = Tree[p].val * (Tree[q].val + x) % Mod; Rub[++ top] = q; return ; }
    int Mid = l + r >> 1; PushDown(p); PushDown(q);
    Merge(ls(p), ls(q), l, Mid, x); Merge(rs(p), rs(q), Mid + 1, r, x);
    Rub[++ top] = q;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

inline void Solve(int u, int fa)
{
    Modify(Root[u], 1, n, dis[u] - a[u] + 1, dis[u]);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        Solve(v, u);
        Merge(Root[u], Root[v], 1, n, Query(Root[v], 1, n, dis[v]));
    }
}

signed main()
{
    freopen("destiny.in", "r", stdin);
    freopen("destiny.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    scanf("%lld", &m);
    REP(i, 1, n) a[i] = dis[i];
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); a[v] = min(a[v], dis[v] - dis[u]); }
    Solve(1, 0);
    printf("%lld\n", (Query(Root[1], 1, n, 1) + Mod) % Mod);
    return 0;
}

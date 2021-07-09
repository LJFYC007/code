/***************************************************************
	File name: CF1172E.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 19时22分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define fa(x) Tree[x].fa
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, ret, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans[maxn], Stack[maxn], tot, f[maxn];
struct node { int son[2], fa, lazy, size1, size2, sum1, sum2, pos1, pos2; } Tree[maxn];
vector<pii> Q[maxn];
bool vis[maxn];

inline bool IsRoot(int x) { return (ls(fa(x)) == x || rs(fa(x)) == x) ? false : true; }

inline int sqr(int x) { return x * x; }

inline void PushUp(int root) 
{ 
    Tree[root].size1 = Tree[ls(root)].size1 + Tree[rs(root)].size1 + Tree[root].size2 + 1;
    Tree[root].sum1 = sqr(Tree[ls(root)].size1) + sqr(Tree[rs(root)].size1) + Tree[root].sum2;
    // Tree[root].pos1 = Tree[ls(root)].pos1 + Tree[rs(root)].pos1 + Tree[root].pos2 + (vis[root] ? root : 0);
}

inline void PushTag(int root) { Tree[root].lazy ^= 1; swap(ls(root), rs(root)); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ; Tree[root].lazy ^= 1;
    if ( ls(root) ) PushTag(ls(root)); if ( rs(root) ) PushTag(rs(root));
}

inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    if ( w ) fa(w) = y; fa(y) = x; fa(x) = z;
    PushUp(y);
}

inline void Splay(int x)
{
    int y = x, z; tot = 0;
    while ( !IsRoot(y) ) { Stack[++ tot] = y; y = fa(y); }
    PushDown(y); while ( tot ) PushDown(Stack[tot --]);
    while ( !IsRoot(x) ) 
    {
        y = fa(x); z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
    PushUp(x);
}

inline void Access(int root)
{
    for ( int x = 0; root; x = root, root = fa(root) ) 
    {
        Splay(root); 
        Tree[root].size2 += Tree[rs(root)].size1 - Tree[x].size1;
        Tree[root].sum2 += sqr(Tree[rs(root)].size1) - sqr(Tree[x].size1);
        // Tree[root].pos2 += Tree[rs(root)].pos1 - Tree[x].pos1;
        rs(root) = x; PushUp(root);
    }
}

inline void MakeRoot(int root) { Access(root); Splay(root); PushTag(root); } 

inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; }

inline void Link(int u, int v)
{
    MakeRoot(u); if ( FindRoot(v) == u ) return ;
    Tree[v].size2 += Tree[u].size1; Tree[v].sum2 += sqr(Tree[u].size1); // Tree[v].pos2 += Tree[u].pos1;
    fa(u) = v; PushUp(v); Splay(v); 
}

inline void Cut(int u, int v) { MakeRoot(u); if ( FindRoot(v) == u ) { fa(v) = rs(u) = 0; PushUp(u); } }

inline int Get(int x)
{
    while ( !vis[x] ) x = f[x]; MakeRoot(x);
    return Tree[x].sum1;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    Link(f[u], u);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; DFS(v, u);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld", &c[i]); Q[c[i]].push_back(pii(-i, 0)); }
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, m) 
    { 
        int u, x; scanf("%lld%lld", &u, &x); 
        Q[x].push_back(pii(-u, i)); Q[c[u]].push_back(pii(u, i));
        c[u] = x;
    }
    REP(i, 1, n) Q[c[i]].push_back(pii(i, m + 1));
    vis[n + 1] = true; Tree[n + 1].pos1 = n + 1; f[1] = n + 1; DFS(1, 0);
    REP(c, 1, n) for ( auto i : Q[c] ) 
    {
        int u = i.first; ret = 0;
        if ( u > 0 ) 
        {
            ret -= Get(u); ret -= Get(f[u]); vis[u] = false;
            Link(u, f[u]); ret += Get(u);
        }
        else
        {
            u = -u; ret -= Get(u); 
            Cut(u, f[u]); vis[u] = true;
            ret += Get(u); ret += Get(f[u]);
        }
        ans[i.second] += ret;
    }
    REP(i, 1, m) ans[i] += ans[i - 1]; 
    REP(i, 0, m) printf("%lld\n", -ans[i]);
    return 0;
}

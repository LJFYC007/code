/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月03日 星期三 19时13分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 1e9 + 7;

int n, N, tot = 1, last = 1, f[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], son[maxn], top[maxn], size[maxn], p[maxn], id[maxn], cnt, anc[maxn];
struct node1 { int fa, Next[26], len; } Trie[maxn];
struct node2 { int sum, lazy, val; } Tree[maxn << 2];
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root) 
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy += Tree[root].lazy;
    Tree[rson].lazy += Tree[root].lazy;
    Tree[lson].sum = (Tree[lson].sum + Tree[lson].val * Tree[root].lazy) % Mod;
    Tree[rson].sum = (Tree[rson].sum + Tree[rson].val * Tree[root].lazy) % Mod;
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    {
        Tree[root].val = Trie[id[l]].len - Trie[Trie[id[l]].fa].len;
        return ;
    }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].val = Tree[lson].val + Tree[rson].val;
}

inline void Modify(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    { 
        ++ Tree[root].lazy; 
        Tree[root].sum = (Tree[root].sum + Tree[root].val) % Mod; 
        return ; 
    } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum % Mod;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret % Mod;
}

inline void Solve1(int x)
{
    while ( top[x] != 1 ) { Modify(1, 1, N, p[top[x]], p[x]); x = anc[top[x]]; }
    Modify(1, 1, N, p[1], p[x]);
}

inline int Solve2(int x)
{
    int ret = 0;
    while ( top[x] != 1 ) { ret += Query(1, 1, N, p[top[x]], p[x]); x = anc[top[x]]; }
    ret += Query(1, 1, N, p[1], p[x]);
    return ret % Mod;
}

inline void Extand(int c)
{
    int p = last, cur = ++ tot; Trie[cur].len = Trie[last].len + 1; last = cur;
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; }
    if ( !p ) { Trie[cur].fa = 1; return ; }
    int q = Trie[p].Next[c];
    if ( Trie[q].len == Trie[p].len + 1 ) { Trie[cur].fa = q; return ; }
    int clone = ++ tot; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1; 
    while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; }
    Trie[cur].fa = Trie[q].fa = clone;
}

inline void DFS1(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v] = u;
        DFS1(v, u); size[u] += size[v];
        if ( size[v] > size[son[u]] ) son[u] = v;
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t; p[u] = ++ cnt; id[cnt] = u;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == anc[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld", &n); scanf("%s", s + 1);    
    REP(i, 1, n) Extand(s[i] - 'a');
    REP(i, 2, tot) add(Trie[i].fa, i);
    N = tot;
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, N);
    int pos = 1;
    REP(i, 1, n)
    {
        pos = Trie[pos].Next[s[i] - 'a'];
        f[i] = (f[i - 1] + Solve2(pos)) % Mod; 
        Solve1(pos); 
    }
    REP(i, 1, n) { f[i] = (f[i] + f[i - 1]) % Mod; printf("%lld\n", (f[i] + Mod) % Mod); }
    return 0;
}

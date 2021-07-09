/***************************************************************
	File name: P4482.cpp
	Author: ljfcnyali
	Create time: 2021年01月03日 星期日 09时38分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 0x3f3f3f3f;

int n, q, lst = 1, tot = 1, cnt, ans[maxn], f[maxn], g[maxn], anc[maxn], size[maxn], son[maxn], top[maxn], Root[maxn], ROOT;
char s[maxn];
struct node { int len, fa, Next[26]; } Trie[maxn];
struct NODE 
{ 
    int l, r, id; 
    NODE(int a = 0, int b = 0, int c = 0) { l = a; r = b; id = c; }
} Q[maxn];
vector<int> Edge[maxn];
vector<NODE> p[maxn];
struct Node { int lson, rson, val; } Tree[maxn << 5];

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !pos ) return ; 
    if ( !root ) { root = ++ cnt; Tree[root].val = INF; ls(root) = rs(root) = 0; } 
    if ( l == r ) { Tree[root].val = min(Tree[root].val, val); return ; } 
    int Mid = l + r >> 1; if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val); else Modify(rs(root), Mid + 1, r, pos, val);
    Tree[root].val = min(Tree[ls(root)].val, Tree[rs(root)].val);
}

inline int Query(int root, int l, int r, int pos, int lim)
{
    if ( !root || Tree[root].val >= lim ) return 0;
    if ( l == r ) return l;
    int Mid = l + r >> 1, ret = 0;
    if ( pos <= Mid + 1 ) return Query(ls(root), l, Mid, pos, lim);
    ret = Query(rs(root), Mid + 1, r, pos, lim);
    return ret ? ret : Query(ls(root), l, Mid, pos, lim);
}

inline void Merge(int &p, int q, int l, int r)
{
    if ( !p || !q ) { p += q; return ; } 
    if ( l == r ) { Tree[p].val = min(Tree[p].val, Tree[q].val); return ; } 
    int Mid = l + r >> 1; Merge(ls(p), ls(q), l, Mid); Merge(rs(p), rs(q), Mid + 1, r);
    Tree[p].val = min(Tree[ls(p)].val, Tree[rs(p)].val);
}

inline void Extend(int c)
{
    int cur = ++ tot; Trie[cur].len = Trie[lst].len + 1; int p = lst; lst = cur; 
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; } 
    if ( !p ) { Trie[cur].fa = 1; return ; }
    int q = Trie[p].Next[c];
    if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; } 
    int clone = ++ tot; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
    while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; } 
    Trie[cur].fa = Trie[q].fa = clone;
}

inline void DFS1(int u)
{
    size[u] = 1; anc[u] = Trie[u].fa; int Max = 0;
    for ( auto v : Edge[u] ) 
    {
        DFS1(v); size[u] += size[v]; 
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    top[u] = t; if ( son[u] ) DFS2(son[u], t);
    for ( auto v : Edge[u] ) if ( v != son[u] ) DFS2(v, v);
}

inline void Insert(int u, NODE x) { while ( u ) { p[u].push_back(x); u = anc[top[u]]; } }

inline void Find(int u, int x)
{
    Modify(ROOT, 1, n, g[u], g[u] - x);
    for ( auto v : Edge[u] ) Find(v, x);
}

inline void DFS(int u, int op)
{
    if ( op ) ROOT = cnt = 0;
    Modify(ROOT, 1, n, g[u], g[u] - Trie[u].len);
    for ( auto v : Edge[u] ) if ( son[u] != v ) Find(v, Trie[u].len);
    for ( auto it : p[u] )
    {
        int x = Query(ROOT, 1, n, it.r, it.l);
        ans[it.id] = max(ans[it.id], x < it.l ? 0 : x - it.l + 1);
    }
    if ( son[u] ) DFS(son[u], 0);
    for ( auto v : Edge[u] ) if ( son[u] != v ) DFS(v, 1);
}

inline void DFS3(int u)
{
    for ( auto v : Edge[u] ) { DFS3(v); Merge(Root[u], Root[v], 1, n); }
    Modify(Root[u], 1, n, g[u], g[u]);
    for ( auto it : p[u] ) 
    {
        int x = Query(Root[u], 1, n, it.r, it.l + Trie[u].len);
        ans[it.id] = max(ans[it.id], x < it.l ? 0 : x - it.l + 1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) { f[i] = tot + 1; g[tot + 1] = i; Extend(s[i] - 'a'); }
    REP(i, 2, tot) Edge[Trie[i].fa].push_back(i); 
    DFS1(1); DFS2(1, 1); scanf("%d", &q); Tree[0].val = INF;
    REP(i, 1, q) { int l, r; scanf("%d%d", &l, &r); Insert(f[r], NODE(l, r, i)); }
    DFS(1, 0); cnt = 0; DFS3(1);
    REP(i, 1, q) printf("%d\n", ans[i]);
    return 0;
}

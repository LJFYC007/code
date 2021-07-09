/***************************************************************
	File name: CF666E.cpp
	Author: ljfcnyali
	Create time: 2019年12月25日 星期三 10时05分39秒
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

const int maxn = 5e5 + 10;

int n, m, last = 1, tot = 1, cnt, Root[maxn], anc[maxn][20], Begin[maxn], Next[maxn], To[maxn], e, f[maxn], Max, Pos, g[maxn];
struct node { int Next[26], len, fa; } Trie[maxn];
struct Node { int lson, rson, Max, pos; } Tree[maxn << 5];
char s[maxn], S[maxn];

inline void PushUp(int root)
{
    Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max);
    Tree[root].pos = n + 1;
    if ( ls(root) && Tree[ls(root)].Max == Tree[root].Max ) Tree[root].pos = min(Tree[root].pos, Tree[ls(root)].pos);
    if ( rs(root) && Tree[rs(root)].Max == Tree[root].Max ) Tree[root].pos = min(Tree[root].pos, Tree[rs(root)].pos);
}

inline void Modify(int &root, int l, int r, int pos)
{
    if ( !root ) root = ++ cnt; 
    if ( l == r ) { ++ Tree[root].Max; Tree[root].pos = l; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
    else Modify(rs(root), Mid + 1, r, pos);
    PushUp(root);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = ++ cnt; 
    if ( l == r ) { Tree[root].pos = l; Tree[root].Max = Tree[p].Max + Tree[q].Max; return root; }
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(p), ls(q), l, Mid);
    rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(root); return root;
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return ;
    if ( L <= l && r <= R ) 
    {
        if ( Max < Tree[root].Max ) { Max = Tree[root].Max; Pos = Tree[root].pos; }
        else if ( Max == Tree[root].Max ) Pos = min(Pos, Tree[root].pos); 
        return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) Query(rs(root), Mid + 1, r, L, R);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; anc[v][0] = u; DFS(v);
        Root[u] = Merge(Root[u], Root[v], 1, n);
    }
}

inline void Extand(int c, int x)
{
    int cur = ++ tot; Trie[cur].len = Trie[last].len + 1; Modify(Root[tot], 1, n, x);
    int p = last; last = cur;
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; }
    if ( !p ) { Trie[cur].fa = 1; return ; }
    int q = Trie[p].Next[c];
    if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; }
    int clone = ++ tot; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
    while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; }
    Trie[q].fa = Trie[cur].fa = clone;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%s", S + 1); last = 1; REP(j, 1, str(S + 1)) Extand(S[j] - 'a', i); }
    // puts("");
    REP(i, 2, tot) add(Trie[i].fa, i); DFS(1);
    REP(j, 1, 18) REP(i, 1, tot) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    int p = 1; 
    REP(i, 1, str(s + 1))
    {
        int c = s[i] - 'a'; g[i] = g[i - 1];
        while ( p != 1 && !Trie[p].Next[c] ) { p = Trie[p].fa; g[i] = Trie[p].len; }
        if ( Trie[p].Next[c] ) { p = Trie[p].Next[c]; ++ g[i]; }
        f[i] = p;
    }
    scanf("%d", &m);
    while ( m -- ) 
    {
        int l, r, L, R; scanf("%d%d%d%d", &l, &r, &L, &R);
        p = f[R]; int len = R - L + 1;
        if ( g[R] < len ) { printf("%d 0\n", l); continue ; } 
        for ( int j = 18; j >= 0; -- j ) if ( Trie[anc[p][j]].len >= len ) p = anc[p][j];
        Max = 0; Pos = l;
        Query(Root[p], 1, n, l, r);
        printf("%d %d\n", Pos, Max);
    }
    return 0;
}

/***************************************************************
	File name: CF700E.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 19时05分49秒
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

const int maxn = 1e6 + 10;

int n, last = 1, tot = 1, Begin[maxn], Next[maxn], To[maxn], e, ans;
int anc[maxn][22], Root[maxn], cnt, f[maxn], Max[maxn], g[maxn];
struct node1 { int Next[26], len, fa; } Trie[maxn];
struct node2 { int lson, rson, sum; } Tree[maxn << 4];
char s[maxn];

inline void Modify(int &root, int l, int r, int pos)
{
    if ( !root ) root = ++ cnt;
    ++ Tree[root].sum;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
    else Modify(rs(root), Mid + 1, r, pos);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = ++ cnt;
    Tree[root].sum = Tree[p].sum + Tree[q].sum;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(p), ls(q), l, Mid);
    rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    return root;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
    return ret;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extand(int c, int x)
{
    int cur = ++ tot; Trie[cur].len = Trie[last].len + 1;
    Modify(Root[cur], 1, n, x); Max[cur] = x;
    int p = last; last = cur;
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
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; anc[v][0] = u; DFS1(v); 
        if ( u != 1 ) { Max[u] = max(Max[u], Max[v]); Root[u] = Merge(Root[u], Root[v], 1, n); }
    }
}

inline void DFS2(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( u == 1 ) { f[v] = 1; g[v] = v; }
        else if ( Query(Root[g[u]], 1, n, Max[v] - Trie[v].len + Trie[g[u]].len, Max[v] - 1) )
        {
            f[v] = f[u] + 1; g[v] = v;
        }
        else { f[v] = f[u]; g[v] = g[u]; }
        DFS2(v);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", s + 1);
    REP(i, 1, n) Extand(s[i] - 'a', i);
    REP(i, 2, tot) add(Trie[i].fa, i);
    DFS1(1);
    REP(j, 1, 20) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    f[1] = g[1] = 1; DFS2(1);
    REP(i, 1, tot) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}

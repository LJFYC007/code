/***************************************************************
	File name: CF547E.cpp
	Author: ljfcnyali
	Create time: 2021年01月22日 星期五 15时24分17秒
***************************************************************/
#include <algorithm>
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
const int N = 2e5;

int n, m, q, lst = 1, tot = 1, Root[maxn], L[maxn], R[maxn], f[maxn], cnt, ans[maxn];
struct node { int len, fa, Next[26]; } Trie[maxn];
struct Node { int lson, rson, sum; } Tree[maxn << 4];
struct NODE { int l, r, id; } ;
vector<int> Edge[maxn];
vector<NODE> Q[maxn];
string s[maxn];

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ cnt;
    if ( l == r ) { Tree[root].sum = val; return ; } 
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum;
}

inline void Merge(int &p, int q, int l, int r)
{
    if ( !p || !q ) { p += q; return ; } 
    if ( l == r ) { Tree[p].sum = max(Tree[p].sum, Tree[q].sum); return ; } 
    int Mid = l + r >> 1;
    Merge(ls(p), ls(q), l, Mid); Merge(rs(p), rs(q), Mid + 1, r);
    Tree[p].sum = Tree[ls(p)].sum + Tree[rs(p)].sum;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root || (L <= l && r <= R) ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
    return ret;
}

inline void DFS(int u)
{
    for ( auto v : Edge[u] ) { DFS(v); Merge(Root[u], Root[v], 1, N); }
    for ( auto it : Q[u] ) ans[it.id] = Query(Root[u], 1, N, it.l, it.r);
}

inline void Extend(int c)
{
    int cur = ++ tot, p = lst; lst = cur; Trie[cur].len = Trie[p].len + 1; 
    Modify(Root[cur], 1, N, m, 1);
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; } 
    if ( !p ) { Trie[cur].fa = 1; return ; } 
    int q = Trie[p].Next[c];
    if ( Trie[p].len + 1 == Trie[q].len ) { Trie[cur].fa = q; return ; } 
    int clone = ++ tot; Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
    while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; } 
    Trie[cur].fa = Trie[q].fa = clone;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    REP(i, 1, n)
    {
        cin >> s[i]; lst = 1;
        L[i] = m + 1; for ( auto it : s[i] ) { ++ m; Extend(it - 'a'); } R[i] = m;
    }
    REP(i, 1, n)
    {
        int p = 1; for ( auto it : s[i] ) p = Trie[p].Next[it - 'a'];
        f[i] = p;
    }
    REP(i, 1, q)
    {
        int l, r, t; scanf("%d%d%d", &l, &r, &t);
        l = L[l]; r = R[r]; t = f[t]; Q[t].push_back({l, r, i});
    }
    REP(i, 2, tot) Edge[Trie[i].fa].push_back(i);
    DFS(1); REP(i, 1, q) printf("%d\n", ans[i]);
    return 0;
}

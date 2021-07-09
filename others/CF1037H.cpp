/***************************************************************
	File name: CF1037H.cpp
	Author: ljfcnyali
	Create time: 2019年11月25日 星期一 14时09分15秒
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

const int maxn = 2e5 + 10;

struct SAM { int Next[26], len, fa; } Trie[maxn << 2];
struct node { int lson, rson, sum; } Tree[maxn << 5];
int tot = 1, last = 1, ret, n, m, Root[maxn], Begin[maxn], Next[maxn], To[maxn], e;
vector<int> suf;
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void PushUp(int root) { Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum; }

inline void Modify(int &root, int l, int r, int pos)
{
    if ( !root ) root = ++ ret;
    if ( l == r ) { Tree[root].sum = 1; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
    else Modify(rs(root), Mid + 1, r, pos);
    PushUp(root);
}

inline int Merge(int x, int y, int l, int r)
{
    if ( !x || !y ) return x + y;
    int root = ++ ret; 
    if ( l == r ) { Tree[root].sum = Tree[x].sum + Tree[y].sum; return root; }
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(x), ls(y), l, Mid);
    rs(root) = Merge(rs(x), rs(y), Mid + 1, r);
    PushUp(root);
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

inline void Extand(int c)
{
    int cur = ++ tot;
    Trie[cur].len = Trie[last].len + 1;
    Modify(Root[cur], 1, n, Trie[cur].len);
    int p = last; last = cur;
    while ( p && !Trie[p].Next[c] ) { Trie[p].Next[c] = cur; p = Trie[p].fa; }
    if ( !p ) { Trie[cur].fa = 1; return ; }
    int q = Trie[p].Next[c];
    if ( Trie[p].len + 1 == Trie[q].len ) Trie[cur].fa = q; 
    else
    {
        int clone = ++ tot;
        Trie[clone] = Trie[q]; Trie[clone].len = Trie[p].len + 1;
        while ( p && Trie[p].Next[c] == q ) { Trie[p].Next[c] = clone; p = Trie[p].fa; }
        Trie[cur].fa = Trie[q].fa = clone;
    }
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        DFS(v);
        Root[u] = Merge(Root[u], Root[v], 1, n);
    }
}

inline void Solve(int L, int R)
{
    int p = 1, N = str(s + 1) + 1; 
    suf.clear(); suf.push_back(-1);
    s[N] = 'a' - 1;
    REP(i, 1, N)
    {
        suf.push_back(-1);
        REP(j, s[i] - 'a' + 1, 25) 
        {
            int v = Trie[p].Next[j];
            if ( v && Query(Root[v], 1, n, L + i - 1, R) ) { suf[i] = j; break ; }
        }
        if ( i == N ) break ; 
        p = Trie[p].Next[s[i] - 'a'];
        if ( !p || !Query(Root[p], 1, n, L + i - 1, R) ) break ; 
    }
    while ( !suf.empty() && suf.back() == -1 ) suf.pop_back();
    if ( suf.empty() ) { puts("-1"); return ; }
    REP(i, 1, suf.size() - 2) printf("%c", s[i]);
    printf("%c\n", suf.back() + 'a');
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) Extand(s[i] - 'a');
    REP(i, 2, tot) add(Trie[i].fa, i);
    DFS(1);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int l, r; scanf("%d %d %s", &l, &r, s + 1);
        Solve(l, r);
    }
    return 0;
}

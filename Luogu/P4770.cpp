/***************************************************************
	File name: P4770.cpp
	Author: ljfcnyali
	Create time: 2020年01月17日 星期五 20时24分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e6 + 10;

char s[maxn];
int n, m, tot = 1, last = 1, cnt, N, ans, Max[maxn], f[maxn], Root[maxn];
int Begin[maxn], Next[maxn], To[maxn], e;
struct node { int Next[26], len, fa; } Trie[2][maxn];
struct Node { int lson, rson, Max; } Tree[maxn << 2];
vector<int> Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void PushUp(int root) { Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max); }

inline void Modify(int &root, int l, int r, int pos)
{
    if ( !root ) root = ++ cnt;
    if ( l == r ) { Tree[root].Max = pos; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
    else Modify(rs(root), Mid + 1, r, pos);
    PushUp(root);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q;
    int root = ++ cnt;
    if ( l == r ) { Tree[root].Max = max(Tree[p].Max, Tree[q].Max); return root; }
    int Mid = l + r >> 1;
    ls(root) = Merge(ls(p), ls(q), l, Mid);
    rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(root); return root;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Mid = l + r >> 1, Max = 0;
    if ( L <= Mid ) Max = max(Max, Query(ls(root), l, Mid, L, R));
    if ( Mid < R ) Max = max(Max, Query(rs(root), Mid + 1, r, L, R));
    return Max;
}

inline int NewNode(int op)
{
    ++ tot;
    Trie[op][tot].len = Trie[op][tot].fa = 0;
    REP(i, 0, 25) Trie[op][tot].Next[i] = 0;
    return tot;
}

inline void Extand(int op, int c, int x)
{
    int cur = NewNode(op); Trie[op][cur].len = Trie[op][last].len + 1;
    int p = last; last = cur;
    if ( op == 0 ) Modify(Root[cur], 1, n, x);
    while ( p && !Trie[op][p].Next[c] ) { Trie[op][p].Next[c] = cur; p = Trie[op][p].fa; }
    if ( !p ) { Trie[op][cur].fa = 1; return ; }
    int q = Trie[op][p].Next[c]; 
    if ( Trie[op][p].len + 1 == Trie[op][q].len ) { Trie[op][cur].fa = q; return ; }
    int clone = NewNode(op); Trie[op][clone] = Trie[op][q]; Trie[op][clone].len = Trie[op][p].len + 1;
    while ( p && Trie[op][p].Next[c] == q ) { Trie[op][p].Next[c] = clone; p = Trie[op][p].fa; }
    Trie[op][q].fa = Trie[op][cur].fa = clone;
}

inline void DFS1(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS1(v);
        Root[u] = Merge(Root[u], Root[v], 1, n);
    }
}

inline void DFS(int u)
{
    for ( auto v : Edge[u] ) 
    {
        DFS(v);
        Max[u] = max(Max[u], Max[v]);
    }
    int L = 1, R = f[Max[u]];
    L = max(L, Trie[1][Trie[1][u].fa].len + 1);
    R = min(R, Trie[1][u].len);
    ans += Trie[1][u].len - Trie[1][Trie[1][u].fa].len - max(0ll, R - L + 1);
}

inline int Check(int x, int l, int r)
{
    int pos = Query(Root[x], 1, n, l, r);
    printf("%lld %lld %lld\n", pos, l, r);
    if ( pos == 0 ) return 0;
    return pos - l + 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) Extand(0, s[i] - 'a', i);
    N = tot; 
    REP(i, 2, N) add(Trie[0][i].fa, i);
    DFS1(1);
    scanf("%lld", &m);
    while ( m -- ) 
    {
        scanf("%s", s + 1); n = str(s + 1);
        REP(i, 0, 25) Trie[1][1].Next[i] = 0;
        REP(i, 1, tot) Max[i] = 0; tot = last = 1; ans = 0;
        REP(i, 1, n) { Max[tot + 1] = i; Extand(1, s[i] - 'a', i); }
        int l, r; scanf("%lld%lld", &l, &r);
        int p = 1, len = 0;
        REP(i, 1, n)
        {
            int c = s[i] - 'a';
            while ( p != 1 && (!Trie[0][p].Next[c] || !Check(Trie[0][p].Next[c], l, r)) ) { p = Trie[0][p].fa; len = Trie[0][p].len; }
            if ( Trie[0][p].Next[c] && Check(Trie[0][p].Next[c], l, r) ) { p = Trie[0][p].Next[c]; ++ len; }
            len = min(len, Check(p, l, r));
            f[i] = len; 
            printf("%lld %lld\n", Check(p, l, r), f[i]);
        }
        puts("");
        REP(i, 1, tot) Edge[i].clear();
        REP(i, 2, tot) Edge[Trie[1][i].fa].push_back(i);
        DFS(1);
        printf("%lld\n", ans);
    }
    return 0;
}

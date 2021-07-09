/***************************************************************
	File name: chocolate.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 20时35分01秒
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

int n, m, tot, N, dfn[maxn], cnt, size[maxn], Root[maxn], c[2][maxn], belong[maxn];
pii a[maxn], b[maxn];
LL ans;
struct node { int Next[26]; } Trie[maxn];
struct Node { int lson, rson, val1, val2; } Tree[maxn << 4];
char s[maxn];
vector<int> p;

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val, int op) { for ( int i = pos; i <= N; i += lowbit(i) ) c[op][i] += val; }

inline int Query(int pos, int op) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[op][i]; return ret; }

inline int Insert(int l, int r, int op)
{
    int p = 1;
    if ( op ) REP(i, l, r)
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot;
        p = Trie[p].Next[c];
    }
    else for ( int i = l; i >= r; -- i ) 
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot;
        p = Trie[p].Next[c];
    }
    return p;
}

inline void DFS(int u)
{
    dfn[u] = ++ cnt; size[u] = 1;
    REP(i, 0, 25)
    {
        int v = Trie[u].Next[i]; if ( !v ) continue ;
        DFS(v); size[u] += size[v];
    }
}

inline void PushDown(int root)
{
    if ( !Tree[root].val2 ) return ;
    if ( !ls(root) ) ls(root) = ++ cnt; Tree[ls(root)].val2 += Tree[root].val2; 
    if ( !rs(root) ) rs(root) = ++ cnt; Tree[rs(root)].val2 += Tree[root].val2; 
    Tree[root].val2 = 0;
}

inline void Modify2(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ cnt; Tree[root].val1 += val;
    if ( l == r ) return ; 
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify2(ls(root), l, Mid, pos, val);
    else Modify2(rs(root), Mid + 1, r, pos, val);
}

inline void Modify3(int &root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( !root ) root = ++ cnt;
    if ( L <= l && r <= R ) { Tree[root].val2 += val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify3(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify3(rs(root), Mid + 1, r, L, R, val);
}

inline int Query2(int root, int l, int r, int L, int R)
{
    if ( !root || L > R ) return 0;
    if ( L <= l && r <= R ) return Tree[root].val1;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query2(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query2(rs(root), Mid + 1, r, L, R);
    return ret;
}

inline int Query3(int root, int l, int r, int pos)
{
    if ( !root ) return 0;
    if ( l == r ) return Tree[root].val2;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query3(ls(root), l, Mid, pos);
    return Query3(rs(root), Mid + 1, r, pos);
}

inline void Modify1(int pos, int x, int val)
{
    for ( int i = pos; i <= N; i += lowbit(i) ) 
    {
        Modify2(Root[i], 1, N, b[x].first, val);
        Modify3(Root[i], 1, N, b[x].first, b[x].second, val);
        Modify(b[x].first, val, 0);
        Modify(b[x].first, val, 1); Modify(b[x].second + 1, -val, 1);
    }
}

inline int Query1(int x, int y)
{
    int ret = 0;
    for ( int i = b[x].second; i > 0; i -= lowbit(i) ) 
    {
        ret += Query2(Root[i], 1, N, b[y].first + 1, b[y].second);
        // ret += Query(b[y].second, 0) - Query(b[y].first, 0);
        ret += Query(b[y].first, 1);
    }
    for ( int i = b[x].first - 1; i > 0; i -= lowbit(i) ) 
    {
        // ret -= Query(b[y].second, 0) - Query(b[y].first, 0);
        ret -= Query2(Root[i], 1, N, b[y].first + 1, b[y].second);
        ret -= Query(b[y].first, 1);
    }
    return ret;
}

int main()
{
    freopen("chocolate.in", "r", stdin);
    freopen("chocolate.out", "w", stdout);
    tot = 1; REP(i, 0, 25) Trie[0].Next[i] = 1;
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%s", s + 1); 
        m = 0; while ( s[m + 1] != '#' ) ++ m; a[i].first = Insert(1, m, 1);
        m = str(s + 1) + 1; while ( s[m - 1] != '#' ) -- m; a[i].second = Insert(str(s + 1), m, 0);
    }
    sort(a + 1, a + n + 1); DFS(1); 
    REP(i, 1, n)
    {
        int x = a[i].first; p.push_back(dfn[x]); p.push_back(dfn[x] + size[x] - 1);
        x = a[i].second; p.push_back(dfn[x]); p.push_back(dfn[x] + size[x] - 1);
    }
    sort(p.begin(), p.end()); N = unique(p.begin(), p.end()) - p.begin(); 
    for ( int i = 0; i < N; ++ i ) belong[p[i]] = i + 1;
    REP(i, 1, tot) b[i] = pii(belong[dfn[i]], belong[dfn[i] + size[i] - 1]);

    REP(i, 1, n) Modify1(b[a[i].first].first, a[i].second, 1);
    REP(i, 1, n)
    {
        Modify1(b[a[i].first].first, a[i].second, -1);
        ans += Query1(a[i].first, a[i].second);
    }
    printf("%lld\n", ans);
    return 0;
}

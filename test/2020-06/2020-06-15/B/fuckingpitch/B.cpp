/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 08时44分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, N;
multiset<int> num[maxn], g[maxn];
char s[maxn], t[maxn], f[51][51];
struct Node { string s; int L, len, sum; vector<int> ans, pre, suf; } Q[maxn];
struct node { int lazy, sum; char c; } Tree[maxn << 2];

namespace SAM
{
    int last, tot = 1, Begin[maxn], Next[maxn], To[maxn], e;
    multiset<int> Set[maxn];
    struct node { int Next[26], fa, len; } Tree[maxn];

    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void Extend(int c)
    {
        int cur = ++ tot, p = last; last = tot; Tree[cur].len = Tree[p].len + 1;
        while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
        if ( !p ) { Tree[cur].fa = 1; return ; }
        int q = Tree[p].Next[c];
        if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
        int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
        while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
        Tree[q].fa = Tree[cur].fa = clone;
    }

    inline void DFS(int u)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            for ( auto j : Set[u] ) Set[v].insert(j);
            DFS(v);
        }
    }

    inline void INIT() 
    { 
        REP(i, 2, tot) add(Tree[i].fa, i);
        DFS(1);
        int p = 1, len = 0;
        REP(i, 1, str(s + 1))
        {
            int c = s[i] - 'a';
            while ( p && !Tree[p].Next[c] ) { p = Tree[p].fa; len = Tree[p].len; }
            if ( Tree[p].Next[c] ) { ++ len; p = Tree[p].Next[c]; }
            if ( !p ) { p = 1; len = 0; }
            num[i].clear();
            for ( auto j : SAM :: Set[p] ) if ( j <= len ) num[i].insert(j);
        }
    }
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushTag(int root, int x, int l, int r)
{
    Tree[root].lazy = x;
    if ( l == r ) 
    {
        Tree[root].c = Q[x].s[(l - Q[x].L) % Q[x].len + 1];
        Tree[root].sum = Q[x].ans[(l - Q[x].L) % Q[x].len + 1];
        return ;
    }
    int posl = (l - Q[x].L) / Q[x].len, posr = (r - Q[x].L) / Q[x].len;
    Tree[root].sum = (posr - posl) * Q[x].sum;
    // cout << Tree[root].sum << endl;
    if ( posl != posr ) Tree[root].sum += Q[x].suf[(l - Q[x].L) % Q[x].len + 1] + Q[x].pre[(r - Q[x].L) % Q[x].len + 1];
    else Tree[root].sum += Q[x].pre[(r - Q[x].L) % Q[x].len + 1] - Q[x].pre[(l - Q[x].L) % Q[x].len];
    // cout << l << " " << r << " " << x << " " << Tree[root].sum << endl;
}

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    int Mid = l + r >> 1;
    PushTag(lson, x, l, Mid); PushTag(rson, x, Mid + 1, r);
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].c = s[l]; Tree[root].sum = num[l].size(); return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int x)
{
    cout << root << " " << l << " " << r << " " << L << " " << R << " " << x << endl;
    if ( L <= l && r <= R ) { PushTag(root, x, l, r); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}

inline char Find(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].c;
    if ( Tree[root].lazy ) 
    {
        int x = Tree[root].lazy; 
        return Q[x].s[(pos - Q[x].L) % Q[x].len + 1];
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) return Find(lson, l, Mid, pos);
    return Find(rson, Mid + 1, r, pos);
}

inline void Update(int root, int l, int r, int pos, int x, char c)
{
    if ( l == r ) { Tree[root].sum = x; Tree[root].c = c; return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( pos <= Mid ) Update(lson, l, Mid, pos, x, c);
    else Update(rson, Mid + 1, r, pos, x, c);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    cout << root << " " << l << " " << r << " " << L << " " << R << " " << Tree[root].sum << endl;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root, l, r);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        scanf("%s", f[i] + 1); SAM :: last = 1;
        int len = str(f[i] + 1);
        REP(j, 1, len) SAM :: Extend(f[i][j] - 'a');
        N = max(N, len);
    }
    REP(i, 1, n)
    {
        int p = 1;
        REP(j, 1, str(f[i] + 1)) p = SAM :: Tree[p].Next[f[i][j] - 'a'];
        SAM :: Set[p].insert(str(f[i] + 1));
    }
    scanf("%s", s + 1); SAM :: INIT(); n = str(s + 1); Build(1, 1, n);
    int o = 0;
    while ( m -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%s", t + 1); ++ o;
            int len = str(t + 1), ll = len, x = N;
            N = max(N, len); 
            
            Q[o].len = len; Q[o].L = l; 
            Q[o].s.resize(len + 1);
            REP(i, 1, len) Q[o].s[i] = t[i];

            while ( ll <= N + len ) { REP(i, ll + 1, ll + len) t[i] = t[i - ll]; ll += len; }
        
            int L = max(1, l - N), R = min(n, l + N);
            REP(i, L, l - 1) s[i] = Find(1, 1, n, i);
            REP(i, l, min(r, R)) s[i] = t[(i - l) % len + 1];
            int p = 1, Len = 0;
            REP(i, L, R)
            {
                int c = s[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i >= l ) 
                {
                    num[i].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) num[i].insert(j);
                    Update(1, 1, n, i, num[i].size(), s[i]);
                }
            }

            L = max(1, r - N), R = min(n, r + N); p = 1; Len = 0;
            REP(i, r + 1, R) s[i] = Find(1, 1, n, i);
            REP(i, max(l, L), r) s[i] = t[(i - l) % len + 1];
            REP(i, L, R)
            {
                int c = s[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i > r ) 
                {
                    num[i].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) num[i].insert(j);
                    Update(1, 1, n, i, num[i].size(), s[i]);
                }
            }

            p = 1; Len = 0;
            REP(i, 1, ll)
            {
                int c = t[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i > N ) 
                {
                    g[(i - 1) % len + 1].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) g[(i - 1) % len + 1].insert(j);
                }
            }

            Q[o].ans.resize(len + 1); REP(i, 1, len) Q[o].ans[i] = g[i].size();
            Q[o].sum = 0; REP(i, 1, len) Q[o].sum += Q[o].ans[i];
            Q[o].pre.resize(len + 1); REP(i, 1, len) Q[o].pre[i] = Q[o].ans[i] + Q[o].pre[i - 1];
            Q[o].suf.resize(len + 1); for ( int i = len; i >= 1; -- i ) Q[o].suf[i] = Q[o].ans[i] + (i < len ? Q[o].suf[i + 1] : 0);
            if ( l + N + 1 <= r ) Modify(1, 1, n, l + N + 1, r, o);
            N = x;
        }
        else 
        {
            int ans = 0, p = 1, len = 0;
            REP(i, l, min(r, l + N)) s[i] = Find(1, 1, n, i);
            REP(i, l, min(r, l + N)) 
            {
                int c = s[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ len; }
                if ( !p ) { p = 1; len = 0; }
                for ( auto j : SAM :: Set[p] ) if ( j <= len ) ++ ans;
            }
            cout << ans << endl;
            if ( l + N + 1 <= r ) ans += Query(1, 1, n, l + N + 1, r);
            printf("%d\n", ans);
        }
    }
    return 0;
}

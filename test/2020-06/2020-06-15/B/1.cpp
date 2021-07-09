/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年06月15日 星期一 14时10分00秒
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
 
int n, m, q, N, Next[maxn];
char s[maxn];
struct QaQ { int l, r, pos, len; } g[maxn];
pii anc[51][17][maxn];
struct node { pii f[51]; int lazy; } Tree[maxn << 2];
struct Node { int Next[26], val; } Trie[maxn];
 
inline void PushUp(int root)
{
    REP(i, 0, N)
    {
        int pos = Tree[rson].f[Tree[lson].f[i].first].first;
        int val = Tree[lson].f[i].second + Tree[rson].f[Tree[lson].f[i].first].second;
        Tree[root].f[i] = pii(pos, val);
    }
}
 
inline void PushTag(int root, int l, int r, int x)
{
    Tree[root].lazy = x;
    REP(i, 0, N)
    {
        int posl = l - g[x].pos + 1, posr = r - g[x].pos + 1;
        int pos = i, val = 0;
        for ( int j = 16; j >= 0; -- j ) 
        {
            if ( posl + (1 << j) > posr + 1 ) continue ;
            val += anc[pos][j][g[x].l + (posl - 1) % g[x].len].second;
            pos = anc[pos][j][g[x].l + (posl - 1) % g[x].len].first;
            posl += (1 << j);
        }
        Tree[root].f[i] = pii(pos, val);
    }
}
 
inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].lazy ) return ;
    int Mid = l + r >> 1;
    PushTag(lson, l, Mid, Tree[root].lazy);
    PushTag(rson, Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = 0;
}
 
inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    {
        int c = s[l] - 'a';
        REP(i, 0, N) Tree[root].f[i] = pii(Trie[i].Next[c], Trie[Trie[i].Next[c]].val);
        return ;
    }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}
 
inline void Modify(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, x); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}
 
inline void Query(int root, int l, int r, int L, int R, pii &x)
{
    if ( L <= l && r <= R ) 
    {
        x = pii(Tree[root].f[x.first].first, x.second + Tree[root].f[x.first].second);
        return ;
    }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Query(lson, l, Mid, L, R, x);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R, x);
}
 
inline void Insert()
{
    int n = str(s + 1), p = 0;
    REP(i, 1, n)
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ N;
        p = Trie[p].Next[c];
    }
    ++ Trie[p].val;
}
 
inline void BFS()
{
    queue<int> Q; REP(i, 0, 25) if ( Trie[0].Next[i] ) Q.push(Trie[0].Next[i]);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 25)
        {
            if ( !Trie[u].Next[i] ) { Trie[u].Next[i] = Trie[Next[u]].Next[i]; continue ; }
            Next[Trie[u].Next[i]] = Trie[Next[u]].Next[i];
            Q.push(Trie[u].Next[i]);
        }
    }
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    REP(i, 1, n) { scanf("%s", s + 1); Insert(); }
    BFS(); scanf("%s", s + 1); n = str(s + 1); Build(1, 1, n);
    int o = 0;
    while ( q -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%s", s + 1); m = str(s + 1);
            ++ o; 
            g[o].l = g[o - 1].r + 1; g[o].r = g[o - 1].r + m;
            g[o].pos = l; g[o].len = m;
             
            REP(j, 0, N) REP(k, 1, m) anc[j][0][g[o].l + k - 1] = pii(Trie[j].Next[s[k] - 'a'], Trie[Trie[j].Next[s[k] - 'a']].val);
            REP(i, 1, 16) REP(j, 0, N) REP(k, 1, m)
            {
                int x = anc[j][i - 1][g[o].l + k - 1].first;
                int pos = anc[x][i - 1][g[o].l + (k + (1 << i - 1) - 1) % m].first;
                int val = anc[j][i - 1][g[o].l + k - 1].second + anc[x][i - 1][g[o].l + (k + (1 << i - 1) - 1) % m].second;
                anc[j][i][g[o].l + k - 1] = pii(pos, val);
            }
 
            Modify(1, 1, n, l, r, o);
        }
        else
        {
            pii x = pii(0, 0);
            Query(1, 1, n, l, r, x);
            printf("%d\n", x.second);
        }
    }
    return 0;
}

/***************************************************************
	File name: P4585.cpp
	Author: ljfcnyali
	Create time: 2020年01月15日 星期三 15时10分44秒
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

const int maxn = 2e5 + 10;

int n, m, a[maxn], ans[maxn], Root[maxn], tot, id, num, N;
struct node { int l, r, x, id; node(int L, int R, int X, int ID) { l = L; r = R; x = X; id = ID; } } ;
struct node1 { int son[2], sum; } Trie[maxn << 7];
struct node2 { vector<pii> Root; vector<node> a; } Tree[maxn << 2];
vector<pii> Q[maxn];
struct NODE { int op, d, x, l, r, id, val; } QQ[maxn];

inline int Insert(int now, int val, int dep)
{
    int root = ++ tot; Trie[root] = Trie[now]; ++ Trie[root].sum;
    if ( dep == -1 ) return root;
    int c = (val >> dep) & 1;
    Trie[root].son[c] = Insert(Trie[root].son[c], val, dep - 1);
    return root;
}

inline int Query(int p, int q, int val)
{
    int ret = 0;
    for ( int i = 17; i >= 0; -- i )  
    {
        int c = ((val >> i) & 1) ^ 1;
        if ( Trie[Trie[q].son[c]].sum - Trie[Trie[p].son[c]].sum > 0 ) ret |= 1 << i;
        else c ^= 1;
        q = Trie[q].son[c];
        p = Trie[p].son[c];
    }
    return ret;
}

inline void Modify1(int root, int l, int r, int pos, int val, int opt)
{
    if ( Tree[root].Root.size() && Tree[root].Root.back().first == opt ) 
    {
        int x = Insert(Tree[root].Root.back().second, val, 17);
        Tree[root].Root.pop_back();
        Tree[root].Root.push_back(pii(opt, x));
    }
    else 
    { 
        int x = Insert(Tree[root].Root.size() ? Tree[root].Root.back().second : 0, val, 17); 
        Tree[root].Root.push_back(pii(opt, x)); 
    }
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify1(lson, l, Mid, pos, val, opt);
    else Modify1(rson, Mid + 1, r, pos, val, opt);
}

inline void Modify2(int root, int l, int r, int L, int R, node x)
{
    if ( L <= l && r <= R ) { Tree[root].a.push_back(x); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, x);
}

inline void Solve(int root, int l, int r)
{
    for ( auto it : Tree[root].a ) 
    {
        auto itr = -- upper_bound(Tree[root].Root.begin(), Tree[root].Root.end(), pii(it.r, 100001));
        auto itl = -- lower_bound(Tree[root].Root.begin(), Tree[root].Root.end(), pii(it.l, 0));
        if ( Tree[root].Root.size() == 1 ) 
        {
            if ( it.l <= Tree[root].Root.begin() -> first ) itl -> second = 0;
            if ( it.r >= Tree[root].Root.begin() -> first ) itr = Tree[root].Root.begin();
        }
        ans[it.id] = max(ans[it.id], Query(itl -> second, itr -> second, it.x));
    }
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    Solve(lson, l, Mid); Solve(rson, Mid + 1, r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i]); Root[i] = Insert(Root[i - 1], a[i], 17); }
    REP(i, 1, m) 
    {
        scanf("%d", &QQ[i].op);
        if ( QQ[i].op == 0 ) { scanf("%d%d", &QQ[i].x, &QQ[i].val); ++ N; }
        else scanf("%d%d%d%d", &QQ[i].l, &QQ[i].r, &QQ[i].x, &QQ[i].d);
    }
    REP(i, 1, m)
    {
        if ( QQ[i].op == 0 ) 
        {
            int x = QQ[i].x, val = QQ[i].val;
            Q[x].push_back(pii(++ num, val));
        }
        else
        {
            int l = QQ[i].l, r = QQ[i].r, L, R, d = QQ[i].d, x = QQ[i].x;
            R = num; L = R - d + 1; ++ id;
            ans[id] = Query(Root[l - 1], Root[r], x);
            if ( d != 0 ) Modify2(1, 1, N, L, R, node(l, r, x, id));
        }
    }
    REP(i, 1, n) for ( auto it : Q[i] ) Modify1(1, 1, N, it.first, it.second, i);
    Solve(1, 1, N);
    REP(i, 1, id) printf("%d\n", ans[i]);
    return 0;
}

/***************************************************************
	File name: segtree.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 19时58分31秒
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

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], Pos, MIN, LLL, RRR;
vector<pii> ans;
struct node { int Min, lazy; } Tree[maxn << 2];

inline void PushUp(int root) { Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    if ( Tree[lson].Min < Tree[root].lazy ) Tree[lson].Min = Tree[lson].lazy = Tree[root].lazy;
    if ( Tree[rson].Min < Tree[root].lazy ) Tree[rson].Min = Tree[rson].lazy = Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Min = a[l]; return ; }
    int Mid = l + r >> 1; 
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void add(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Tree[root].Min = val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) add(lson, l, Mid, pos, val);
    else add(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( val <= Tree[root].Min ) return ;
    if ( L <= l && r <= R ) { Tree[root].Min = Tree[root].lazy = val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline pii Get(int root, int l, int r)
{
    if ( l == r ) { pii x = pii(Tree[root].Min, l); Tree[root].Min = INF; return x; }
    int Mid = l + r >> 1; pii x; PushDown(root);
    if ( Tree[lson].Min < Tree[rson].Min ) x = Get(lson, l, Mid);
    else x = Get(rson, Mid + 1, r);
    PushUp(root); return x;
}

inline void Query(int root, int l, int r, int L, int R, int val)
{
    if ( Tree[root].Min >= val ) return ;
    if ( L <= l && r <= R ) 
    {
        if ( Tree[root].Min < MIN ) { LLL = l; RRR = r; MIN = Tree[root].Min; Pos = root; }
        return ;
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Query(lson, l, Mid, L, R, val);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R, val);
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("segtree.in", "r", stdin);
    freopen("segtree.out", "w", stdout);
    read(n); REP(i, 1, n) read(a[i]); read(m);
    Build(1, 1, n);
    REP(o, 1, m)
    {
        int op, l, r, x; read(op); read(l); read(r); read(x);
        if ( op == 1 ) Modify(1, 1, n, l, r, x);
        else 
        { 
            ans.clear(); read(m); bool flag = false;
            REP(i, 1, m) 
            {
                Pos = 0; MIN = INF;
                Query(1, 1, n, l, r, x);
                if ( !Pos ) { flag = true; break ; }
                ans.push_back(Get(Pos, LLL, RRR));
            }
            if ( flag ) puts("-1");
            else { for ( auto i : ans ) printf("%d ", i.first); puts(""); }
            for ( auto i : ans ) add(1, 1, n, i.second, i.first);
        }
    }
    return 0;
}

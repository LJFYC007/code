/***************************************************************
	File name: LibreOJ_6507.cpp
	Author: ljfcnyali
	Create time: 2020年11月12日 星期四 11时14分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 2147483647;

int n, m, a[maxn];
struct node { int Min, Max, lazy1, lazy2; } Tree[maxn << 2];

inline void PushUp(int root)
{
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void PushTag(int root, int op, int val)
{
    if ( op == 1 ) 
    {
        Tree[root].Min &= ~val; Tree[root].Max &= ~val; Tree[root].lazy1 |= val;
        Tree[root].lazy2 &= ~val;
    }
    else { Tree[root].Min |= val; Tree[root].Max |= val; Tree[root].lazy2 |= val; }
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy1 != 0 ) 
    {
        PushTag(lson, 1, Tree[root].lazy1);
        PushTag(rson, 1, Tree[root].lazy1);
        Tree[root].lazy1 = 0;
    }
    if ( Tree[root].lazy2 ) 
    {
        PushTag(lson, 2, Tree[root].lazy2);
        PushTag(rson, 2, Tree[root].lazy2);
        Tree[root].lazy2 = 0;
    }
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Min = Tree[root].Max = a[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int op, int val)
{
    // if ( op == 2 && (Tree[root].Min | val) == Tree[root].Min && (Tree[root].Max | val) == Tree[root].Max ) return ;
    // if ( op == 1 && (Tree[root].Max & ~val) == Tree[root].Max && (Tree[root].Min & ~val) == Tree[root].Min ) return ; 
    // cerr << root << " " << l << " " << r<< " " << L << " " << R << " " << op << " " << val << endl;
    if ( L <= l && r <= R && (Tree[root].Min & val) == (Tree[root].Max & val) && (Tree[root].Min | val) == (Tree[root].Max | val) ) 
    { 
        PushTag(root, op, val); return ; 
    }
    // if ( L <= l && r <= R && Tree[root].Min == Tree[root].Max ) { PushTag(root, op, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, op, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, op, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Min;
    int Mid = l + r >> 1, ret = 2147483647; PushDown(root);
    if ( L <= Mid ) ret = min(ret, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ret = min(ret, Query(rson, Mid + 1, r, L, R));
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    Build(1, 1, n);
    while ( m -- ) 
    {
        // if ( m % 1000 == 0 ) cerr << m << endl;
        int op, l, r, x; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) { scanf("%d", &x); if ( !(x == 1 && a[1] == 1 && a[n] == 0) ) Modify(1, 1, n, l, r, 1, ~x); }
        if ( op == 2 ) { scanf("%d", &x); if ( x ) Modify(1, 1, n, l, r, 2, x); }
        if ( op == 3 ) printf("%d\n", Query(1, 1, n, l, r));
    }
    return 0;
}

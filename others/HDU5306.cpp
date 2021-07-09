/***************************************************************
	File name: HDU5306.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 19时36分48秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 4000010;

struct node
{
    int ma, sa, num, lazy, sum;
} Tree[maxn];

int T, n, m, a[maxn];

inline void PushUp(int root)
{
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
    if ( Tree[lson].ma > Tree[rson].ma ) 
    {
        Tree[root].ma = Tree[lson].ma; Tree[root].num = Tree[lson].num;
        Tree[root].sa = max(Tree[lson].sa, Tree[rson].ma);
    }
    else if ( Tree[lson].ma < Tree[rson].ma ) 
    {
        Tree[root].ma = Tree[rson].ma; Tree[root].num = Tree[rson].num;
        Tree[root].sa = max(Tree[rson].sa, Tree[lson].ma);
    }
    else
    {
        Tree[root].ma = Tree[lson].ma; Tree[root].num = Tree[lson].num + Tree[rson].num;
        Tree[root].sa = max(Tree[lson].sa, Tree[rson].sa);
    }
}

inline void PushTag(int root, int val)
{
    if ( Tree[root].ma <= val ) return ; 
    Tree[root].sum -= (Tree[root].ma - val) * Tree[root].num;
    Tree[root].ma = Tree[root].lazy = val;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy == -1 ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = -1;
}

inline void Build(int root, int l, int r)
{
    Tree[root].lazy = -1;
    if ( l == r ) { Tree[root].ma = Tree[root].sum = a[l]; Tree[root].sa = -1; Tree[root].num = 1; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( Tree[root].ma <= val ) return ;
    if ( L <= l && r <= R && Tree[root].sa <= val && val < Tree[root].ma ) { PushTag(root, val); return ; } 
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int QueryMax(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].ma;
    PushDown(root);
    int Mid = l + r >> 1, Max = 0;
    if ( L <= Mid ) Max = max(Max, QueryMax(lson, l, Mid, L, R));
    if ( Mid < R && Tree[rson].ma >= Max ) Max = max(Max, QueryMax(rson, Mid + 1, r, L, R));
    return Max;
}

inline int QuerySum(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    PushDown(root);
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += QuerySum(lson, l, Mid, L, R);
    if ( Mid < R ) sum += QuerySum(rson, Mid + 1, r, L, R);
    return sum;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(T);
    while ( T -- ) 
    {
        read(n); read(m);
        REP(i, 1, n) read(a[i]);
        Build(1, 1, n);
        REP(i, 1, m)
        {
            int opt, l, r, x; read(opt); read(l); read(r);
            if ( opt == 0 ) { int x; read(x); Modify(1, 1, n, l, r, x); }
            if ( opt == 1 ) printf("%lld\n", QueryMax(1, 1, n, l, r));
            if ( opt == 2 ) printf("%lld\n", QuerySum(1, 1, n, l, r));
        }
    }
    return 0;
}

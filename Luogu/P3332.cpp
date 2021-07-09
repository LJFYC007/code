/***************************************************************
    File name: P3332.cpp
    Author: ljfcnyali
    Create time: 2019年07月18日 星期四 20时10分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree2[x].l
#define rs(x) Tree2[x].r
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 50010 * 4;

struct node1
{
    int l, r;
} Tree1[maxn * 80];

struct node2
{
    int l, r, lazy, L, R, len;
    long long sum;
} Tree2[maxn * 80];

int n, m, cnt, Root[maxn], opt, l, r, val, k;

inline void Build(int root, int l, int r)
{
    Tree1[root].l = l; Tree1[root].r = r; 
    if ( l == r ) return ;
    int Mid = (l + r) >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Push_up(int root)
{
    Tree2[root].sum = Tree2[ls(root)].sum + Tree2[rs(root)].sum;
}

inline void Push_down(int root)
{
    if ( !Tree2[root].lazy ) return ;
    int Mid = (Tree2[root].L + Tree2[root].R) >> 1;
    if ( !ls(root) ) 
    {
        ls(root) = ++ cnt;
        Tree2[ls(root)].L = Tree2[root].L;
        Tree2[ls(root)].R = Mid;
        Tree2[ls(root)].len = Mid - Tree2[root].L + 1;
        Tree2[ls(root)].sum = Tree2[ls(root)].lazy = 0;
    }
    if ( !rs(root) ) 
    {
        rs(root) = ++ cnt;
        Tree2[rs(root)].L = Mid + 1;
        Tree2[rs(root)].R = Tree2[root].R;
        Tree2[rs(root)].len = Tree2[root].R - Mid;
        Tree2[rs(root)].sum = Tree2[rs(root)].lazy = 0;
    }
    int lazy = Tree2[root].lazy;
    Tree2[ls(root)].sum += Tree2[ls(root)].len * lazy;
    Tree2[rs(root)].sum += Tree2[rs(root)].len * lazy;
    Tree2[ls(root)].lazy += lazy;
    Tree2[rs(root)].lazy += lazy;
    Tree2[root].lazy = 0;
}

inline void Update2(int &root, int l, int r, int L, int R)
{
    if ( !root ) { root = ++ cnt; Tree2[root].L = l; Tree2[root].R = r; Tree2[root].len = r - l + 1; }
    Tree2[root].sum += R - L + 1;
    if ( L == l && r == R ) 
    {
        ++ Tree2[root].lazy;
        return ;
    }
    int Mid = (l + r) >> 1;
    if ( R <= Mid ) Update2(ls(root), l, Mid, L, R);
    else if ( L > Mid ) Update2(rs(root), Mid + 1, r, L, R);
    else { Update2(ls(root), l, Mid, L, Mid); Update2(rs(root), Mid + 1, r, Mid + 1, R); }
}

inline void Update1(int root, int l, int r, int val, int L, int R)
{
    Update2(Root[root], 1, n, L, R); 
    if ( l == r ) return ;
    int Mid = (l + r) >> 1;
    if ( val <= Mid ) Update1(lson, l, Mid, val, L, R);
    else Update1(rson, Mid + 1, r, val, L, R);
}

inline long long Query2(int root, int l, int r, int L, int R, int lazy)
{
    if ( !root ) return lazy * (R - L + 1);
    if ( L == l && r == R ) return Tree2[root].sum + Tree2[root].len * lazy;
    int Mid = (l + r) >> 1; 
    lazy += Tree2[root].lazy;
    if ( R <= Mid ) return Query2(ls(root), l, Mid, L, R, lazy);
    else if ( L > Mid ) return Query2(rs(root), Mid + 1, r, L, R, lazy);
    else return Query2(ls(root), l, Mid, L, Mid, lazy) + Query2(rs(root), Mid + 1, r, Mid + 1, R, lazy);
}

inline long long Query1(int root, int l, int r, int L, int R, int k)
{
    if ( l == r ) return l;
    long long sum = Query2(Root[rson], 1, n, L, R, 0);
    int Mid = (l + r) >> 1;
    if ( k <= sum ) return Query1(rson, Mid + 1, r, L, R, k);
    else return Query1(lson, l, Mid, L, R, k - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    Build(1, 1, n);
    REP(i, 1, m) 
    { 
        scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 1 ) 
        {
            scanf("%d", &val);
            Update1(1, 1, n, val, l, r);
        }
        else
        {
            scanf("%d", &k);
            printf("%lld\n", Query1(1, 1, n, l, r, k));
        }
    }
    return 0;
}

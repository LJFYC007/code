/***************************************************************
	File name: CF679E.cpp
	Author: ljfcnyali
	Create time: 2021年01月15日 星期五 10时53分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 4e5 + 10;

int n, q, a[maxn];
vector<int> p;
struct node { int Min, lazy, tag; } Tree[maxn];
bool flag;

inline void PushTag(int root, int val)
{
    int x = *lower_bound(p.begin(), p.end(), val) - val;
    Tree[root].lazy = 0; Tree[root].tag = val; Tree[root].Min = x;
}

inline void PushDown(int root)
{
    if ( Tree[root].tag ) 
    {
        Tree[lson].lazy = Tree[rson].lazy = 0;
        Tree[lson].tag = Tree[rson].tag = Tree[root].tag;
        Tree[lson].Min = Tree[rson].Min = Tree[root].Min;
        Tree[root].tag = 0;
    }
    if ( Tree[root].lazy ) 
    {
        Tree[lson].Min -= Tree[root].lazy; Tree[lson].lazy += Tree[root].lazy;
        Tree[rson].Min -= Tree[root].lazy; Tree[rson].lazy += Tree[root].lazy;
        Tree[root].lazy = 0;
    }
}

inline void PushUp(int root) { Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); }

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l ,Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R && Tree[root].Min > val ) 
    {
        Tree[root].Min -= val; Tree[root].lazy += val; 
        return ; 
    }
    if ( L <= l && r <= R && Tree[root].tag ) 
    {
        PushTag(root, Tree[root].tag + Tree[root].lazy + val);
        if ( Tree[root].Min == 0 ) flag = true;
        return ; 
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify2(lson, l ,Mid, L, R, val);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].tag + Tree[root].lazy;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(lson, l, Mid, pos);
    return Query(rson, Mid + 1, r, pos);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q);
    int x = 1; REP(i, 1, 10) { p.push_back(x); x *= 42; } 
    REP(i, 1, n) { scanf("%lld", &a[i]); Modify1(1, 1, n, i, i, a[i]); }
    while ( q -- ) 
    {
        int op, l, r, x; scanf("%lld", &op);
        if ( op == 1 ) { scanf("%lld", &x); printf("%lld\n", Query(1, 1, n, x)); }
        if ( op == 2 ) { scanf("%lld%lld%lld", &l, &r, &x); Modify1(1, 1, n, l, r, x); }
        if ( op == 3 ) 
        {
            scanf("%lld%lld%lld", &l, &r, &x); 
            do
            {
                flag = false;
                Modify2(1, 1, n, l, r, x);
            } while ( flag == true ) ;
        }
    }
    return 0;
}

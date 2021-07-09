/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年11月18日 星期三 11时39分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 4e5 + 10;

int n, q, a[maxn];
struct node { int sum, Min, Max, len, lazy; } Tree[maxn << 2];

inline void PushUp(int root) 
{ 
    Tree[root].Max = Tree[lson].Max; Tree[root].Min = Tree[rson].Min; 
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum; 
}

inline void PushTag(int root, int val)
{
    Tree[root].Min = Tree[root].Max = Tree[root].lazy = val;
    Tree[root].sum = val * Tree[root].len; 
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) { Tree[root].sum = Tree[root].Min = Tree[root].Max = a[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline int Find(int root, int l, int r, int val)
{
    if ( l == r ) return Tree[root].Min <= val ? l : n + 1;
    int Mid = l + r >> 1; PushDown(root);
    if ( Tree[lson].Min > val ) return Find(rson, Mid + 1, r, val);
    return Find(lson, l, Mid, val);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L > R ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

inline int Solve(int root, int l, int r, int val)
{
    if ( l == r ) return l; 
    int Mid = l + r >> 1; PushDown(root);
    if ( val >= Tree[lson].sum + Tree[rson].Max ) return Solve(rson, Mid + 1, r, val - Tree[lson].sum);
    else return Solve(lson, l, Mid, val);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) scanf("%lld", &a[i]);
    Build(1, 1, n);
    while ( q -- ) 
    {
        int t, x, y; scanf("%lld%lld%lld", &t, &x, &y);
        if ( t == 1 ) 
        {
            int pos = Find(1, 1, n, y);
            if ( pos <= x ) Modify(1, 1, n, pos, x, y);
        }
        if ( t == 2 ) 
        {
            int now = max(x, Find(1, 1, n, y)), ans = 0;  
            while ( now <= n ) 
            {
                int pos = Solve(1, 1, n, Query(1, 1, n, 1, now - 1) + y);
                y -= Query(1, 1, n, now, pos); ans += pos - now + 1;
                if ( pos == n ) break ; now = Find(1, 1, n, y);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}

#include "average.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;

LL n = maxn - 10, m, a[maxn];
double ans;
struct node { LL sum, day, pos; double Max; } Tree[maxn << 2];

inline void PushUp(LL root)
{
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
    double val = (Tree[lson].Max * Tree[lson].pos + Tree[rson].sum) / (Tree[lson].pos + Tree[rson].day);
    if ( Tree[rson].Max > val ) { Tree[root].pos = Tree[rson].pos; Tree[root].Max = Tree[rson].Max; }
    else { Tree[root].pos = Tree[lson].pos + Tree[rson].day; Tree[root].Max = val; }
}

inline void Modify(LL root, LL l, LL r, LL pos, LL val)
{
    ++ Tree[root].day;
    if ( l == r ) { Tree[root].sum = Tree[root].Max = val; Tree[root].pos = 1; return ; }
    LL Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val); 
    PushUp(root);
}

inline void Query(LL root, LL l, LL r, LL L, LL R)
{
    if ( L <= l && r <= R ) 
    {
        LL x = m - 1 - r, y = a[m - 1] - a[r];
        double val = (Tree[root].Max * Tree[root].pos + y) / (Tree[root].pos + x);
        ans = max(ans, val);
        return ;
    }
    LL Mid = l + r >> 1;
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

void init()  { }

void addMonth(int K) 
{
    Modify(1, 0, n, m, K);
    a[m] = K; if ( m > 0 ) a[m] += a[m - 1];
    ++ m;
}

double maximumAverage(int L, int R) 
{
    ans = (a[m - 1] - (R > 0 ? a[R - 1] : 0)) * 1.0 / (m - R);
    REP(i, L, R) ans = max(ans, (a[m - 1] - (i > 0 ? a[i - 1] : 0)) * 1.0 / (m - i));
    Query(1, 0, n, L, R);
    return ans;
}

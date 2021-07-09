/***************************************************************
	File name: P4425.cpp
	Author: ljfcnyali
	Create time: 2020年04月13日 星期一 20时31分19秒
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

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, p, a[maxn], N, ans;
struct node { int Max, ret, sum; } Tree[maxn];

inline int Query(int root, int l, int r, int val)
{
    if ( l == r ) return Tree[root].Max <= val ? INF : val + l + 1;
    int Mid = l + r >> 1;
    if ( Tree[rson].Max <= val ) return Query(lson, l, Mid, val);
    return min(Query(rson, Mid + 1, r, val), Tree[root].sum);
}

inline void PushUp(int root, int l, int r)
{
    int Mid = l + r >> 1;
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
    Tree[root].sum = Query(lson, l, Mid, Tree[rson].Max);
    Tree[root].ret = min(Tree[root].sum, Tree[rson].ret);
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Max = a[l] - l; Tree[root].ret = INF; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root, l, r);
}

inline void Modify(int root, int l, int r, int pos)
{
    if ( l == r ) { Tree[root].Max = a[l] - l; Tree[root].ret = INF; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos);
    else Modify(rson, Mid + 1, r, pos);
    PushUp(root, l, r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &p);
    REP(i, 1, n) { scanf("%d", &a[i]); a[i + n] = a[i]; }
    N = 2 * n;
    Build(1, 1, N);
    ans = n - 1 + min(1 + Tree[1].Max, Tree[1].sum);
    printf("%d\n", ans);
    while ( m -- ) 
    {
        int x, y; scanf("%d%d", &x, &y);
        if ( p == 1 ) { x ^= ans; y ^= ans; }
        a[x] = a[x + n] = y;
        Modify(1, 1, N, x); Modify(1, 1, N, x + n);
        ans = n - 1 + min(1 + Tree[1].Max, Tree[1].sum);
        printf("%d\n", ans);
    }
    return 0;
}


/***************************************************************
	File name: P5653.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 21时07分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;

int n, k, a[maxn], ans;
pii suf[maxn];
struct node { int Min, lazy; } Tree[maxn << 2];

inline void PushUp(int root) { Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    Tree[lson].lazy += x; Tree[rson].lazy += x;
    Tree[lson].Min += x; Tree[rson].Min += x;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Min = a[l]; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
    // printf("%lld %lld %lld %lld\n", root, l, r, Tree[root].Min);
    // printf("%lld %lld\n", Tree[lson].Min, Tree[rson].Min);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { Tree[root].Min += val; Tree[root].lazy += val; return ; }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Min;
    PushDown(root);
    int Mid = l + r >> 1, ret = INF;
    if ( L <= Mid ) ret = min(ret, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ret = min(ret, Query(rson, Mid + 1, r, L, R));
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld", &a[i]); a[i] += i * k; }
    REP(i, 1, n) { scanf("%lld", &suf[i].x); suf[i].y = i; }
    for ( int i = n; i >= 1; -- i ) 
    { 
        suf[i].x += suf[i + 1].x; 
        ans -= k * suf[i].x; 
        // a[i] = a[i] - a[i - 1];
    }
    sort(suf + 1, suf + n + 1, [](pii a, pii b) { return a.x > b.x; }); 
    REP(i, 1, 4 * n) Tree[i].Min = INF;
    Build(1, 1, n);
    REP(i, 1, n)
    {
        if ( suf[i].x <= 0 ) break ; 
        int x = min(2 * k, Query(1, 1, n, suf[i].y, n));
        ans += x * suf[i].x;
        // printf("%lld %lld\n", x, suf[i].y);
        Modify(1, 1, n, suf[i].y, n, -x);
    }
    printf("%lld\n", ans);
    return 0;
}

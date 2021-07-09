/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月12日 星期五 10时43分43秒
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

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, k, d[maxn], a[maxn], ans = 1, f[maxn], g[maxn], top;
pii Stack[maxn];
struct node { int Min, lazy, val; } Tree[maxn << 2];

inline void PushUp(int root) { Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    Tree[lson].lazy += x; Tree[lson].Min += x;
    Tree[rson].lazy += x; Tree[rson].Min += x;
}

inline void Build(int root, int l, int r)
{
    Tree[root].Min = INF;
    if ( l == r ) { Tree[root].val = g[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r); 
    Tree[root].val = min(Tree[lson].val, Tree[rson].val);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { Tree[root].lazy += val; Tree[root].Min += val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int Min, int x)
{
    if ( l > x ) return 0;
    if ( Tree[root].val - k > Min ) return 0;
    if ( l == r ) return l;
    int ans = 0, Mid = l + r >> 1; PushDown(root);
    if ( min(Min, Tree[lson].Min) >= Tree[rson].val - k ) 
    {
        ans = Query(rson, Mid + 1, r, min(Min, Tree[lson].Min), x);
        if ( ans ) return ans;
    }
    return Query(lson, l, Mid, Min, x);;
}

inline int Get(int x)
{
    int L = 1, R = top, pos = -1;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Stack[Mid].first >= x ) { pos = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    return Stack[pos - 1].second - 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n - 1) scanf("%lld", &d[i]); 
    REP(i, 1, n) scanf("%lld", &a[i]); 
    REP(i, 1, n)
    {
        f[i] = f[i - 1] + a[i - 1] - d[i - 1];
        g[i] = g[i - 1] + d[i - 1] - a[i];
    }
    Stack[++ top] = pii(-INF, n + 1);
    Build(1, 1, n);
    for ( int i = n; i >= 1; -- i ) 
    {
        Modify(1, 1, n, i, i, -INF + g[i]);
        while ( Stack[top].first >= f[i] ) 
        {
            pii x = Stack[top --];
            if ( Stack[top].second <= n ) 
            {
                int val = x.first - Stack[top].first;
                Modify(1, 1, n, Stack[top].second - 1, n, val);
            }
        }
        if ( Stack[top].second <= n ) 
        {
            int val = f[i] - Stack[top].first;
            Modify(1, 1, n, Stack[top].second - 1, n, -val);
        }
        Stack[++ top] = pii(f[i], i);

        int L = i + 1, R = Get(f[i] - k);
        ans = max(ans, Query(1, 1, n, INF, R) - i + 1);
    }
    printf("%lld\n", ans);
    return 0;
}

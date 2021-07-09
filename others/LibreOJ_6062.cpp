/***************************************************************
	File name: LibreOJ_6062.cpp
	Author: ljfcnyali
	Create time: 2020年05月05日 星期二 21时16分47秒
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

const int maxn = 3e5 + 10;
const int INF = 1e18;

int n, m, h, a[maxn], b[maxn], ans;
struct node { int Min, lazy; } Tree[maxn << 2];

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].Min += Tree[root].lazy;
    Tree[rson].Min += Tree[root].lazy;
    Tree[lson].lazy += Tree[root].lazy;
    Tree[rson].lazy += Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) { Tree[root].Min += x; Tree[root].lazy += x; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Min;
    int Mid = l + r >> 1, ret = INF; PushDown(root);
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
    scanf("%lld%lld%lld", &n, &m, &h);
    REP(i, 1, m) 
    {
        scanf("%lld", &b[i]);
        Modify(1, 1, m, i, i, -i);
    }
    sort(b + 1, b + m + 1);
    REP(i, 1, n) scanf("%lld", &a[i]); 
    REP(i, 1, n)
    {
        int x = lower_bound(b + 1, b + m + 1, h - a[i]) - b;
        if ( x >= 1 ) Modify(1, 1, m, x, m, 1);
        // printf("%lld %lld\n", h - a[i], x);
        // printf("%lld\n", Query(1, 1, m, 1, m));
        if ( i > m ) 
        {
            x = lower_bound(b + 1, b + m + 1, h - a[i - m]) - b;
            if ( x >= 1 ) Modify(1, 1, m, x, m, -1);
        }
        // printf("%lld\n", Query(1, 1, m, 1, m));
        if ( i >= m && Query(1, 1, m, 1, m) >= 0 ) ++ ans; 
    }
    printf("%lld\n", ans);
    return 0;
}

/***************************************************************
	File name: large.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 10时11分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 500010;

int n, m, a[maxn], Stack1[maxn], Stack2[maxn], tot1, tot2, num[maxn];
pair<pii, int> q[maxn];
struct node
{
    int Min, ret, ans, lazy, ti;
} Tree[maxn << 2];

inline void PushTag1(int root, int val) { Tree[root].ans += Tree[root].ret * val; Tree[root].ti += val; }

inline void PushTag2(int root, int val) { Tree[root].Min += val; Tree[root].lazy += val; }

inline void PushUp(int root) 
{
    Tree[root].ans = Tree[lson].ans + Tree[rson].ans;
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].ret = 0;
    if ( Tree[lson].Min == Tree[root].Min ) Tree[root].ret += Tree[lson].ret;
    if ( Tree[rson].Min == Tree[root].Min ) Tree[root].ret += Tree[rson].ret;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy ) { PushTag2(lson, Tree[root].lazy); PushTag2(rson, Tree[root].lazy); Tree[root].lazy = 0; } 
    if ( !Tree[root].ti ) return ;
    if ( Tree[lson].Min == Tree[root].Min ) PushTag1(lson, Tree[root].ti); 
    if ( Tree[rson].Min == Tree[root].Min ) PushTag1(rson, Tree[root].ti);
    Tree[root].ti = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag2(root, val); return ; }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].ans;
    PushDown(root);
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

inline void Build(int root, int l, int r)
{
    Tree[root].Min = l; Tree[root].ret = 1;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

signed main()
{
    freopen("large.in", "r", stdin);
    freopen("large.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    scanf("%lld", &m);
    REP(i, 1, m) { scanf("%lld%lld", &q[i].x.x, &q[i].x.y); q[i].y = i; }
    sort(q + 1, q + m + 1, [](pair<pii, int> a, pair<pii, int> b) { return a.x.y < b.x.y; });
    Build(1, 1, n);
    int j = 1;
    REP(i, 1, n)
    {
        PushTag2(1, -1);
        while ( tot1 && a[Stack1[tot1]] < a[i] ) { Modify(1, 1, n, Stack1[tot1 - 1] + 1, Stack1[tot1], a[i] - a[Stack1[tot1]]); -- tot1; }
        Stack1[++ tot1] = i;
        while ( tot2 && a[Stack2[tot2]] > a[i] ) { Modify(1, 1, n, Stack2[tot2 - 1] + 1, Stack2[tot2], a[Stack2[tot2]] - a[i]); -- tot2; }
        Stack2[++ tot2] = i;
        PushTag1(1, 1);
        while ( j <= m && q[j].x.y == i ) { num[q[j].y] = Query(1, 1, n, q[j].x.x, q[j].x.y); ++ j; }
    }
    REP(i, 1, m) printf("%lld\n", num[i]);
    return 0;
}

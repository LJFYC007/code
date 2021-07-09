/***************************************************************
	File name: water.cpp
	Author: ljfcnyali
	Create time: 2019年10月12日 星期六 11时05分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2000010;
const int N = 1e9;

int n, tot, last, Root;
LL ans;
struct node
{
    int h, l, r;
    bool operator < (const node &a) const { return h < a.h; }
} a[maxn];
struct NODE
{
    int sum, len, lazy, lson, rson;
} Tree[maxn << 2];

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].lazy ) return ;
    int Mid = l + r >> 1;
    if ( !ls(root) ) { ls(root) = ++ tot; Tree[tot].len = Mid - l + 1; }
    Tree[ls(root)].sum = Tree[ls(root)].len - Tree[ls(root)].sum; Tree[ls(root)].lazy ^= 1;
    if ( !rs(root) ) { rs(root) = ++ tot; Tree[tot].len = r - Mid; }
    Tree[rs(root)].sum = Tree[rs(root)].len - Tree[rs(root)].sum; Tree[rs(root)].lazy ^= 1;
    Tree[root].lazy ^= 1;
}

inline void Modify(int &root, int l, int r, int L, int R)
{
    if ( !root ) { root = ++ tot; Tree[root].len = r - l + 1; }
    if ( L <= l && r <= R ) 
    {
        Tree[root].sum = Tree[root].len - Tree[root].sum; Tree[root].lazy ^= 1;
        return ;
    }
    PushDown(root, l, r);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R);
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum;
}

signed main()
{
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int x, y, l, r; scanf("%d%d%d%d", &x, &l, &y, &r);
        a[++ tot].h = x; a[tot].l = l; a[tot].r = r;
        a[++ tot].h = y; a[tot].l = l; a[tot].r = r;
    }
    sort(a + 1, a + tot + 1); tot = Root = 1; Tree[1].len = 1e9 + 1;
    for ( int i = 1; i <= 2 * n; ++ i ) 
    {
        ans += ((LL)a[i].h - last) * Tree[Root].sum;
        int now = i;
        while ( a[now].h == a[i].h && now <= 2 * n ) 
        {
            Modify(Root, 0, N, a[now].l, a[now].r - 1);
            ++ now;
        }
        last = a[i].h; 
        i = now - 1;
    }
    printf("%lld\n", ans);
    return 0;
}

/***************************************************************
	File name: disk.cpp
	Author: ljfcnyali
	Create time: 2020年05月07日 星期四 14时27分11秒
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
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e10;

int n, k, A[maxn], B[maxn], ans;
struct type 
{ 
    int a, b, sum; 
    type(int x = 0, int y = 0, int z = 0) { a = x; b = y; sum = z; }
} ;
type operator + (type x, type y) { return x.sum < y.sum ? x : y; }
type operator * (pii x, pii y) { return type(x.y, y.y, x.x + y.x); }
pii operator + (pii x, pii y) { return x.x < y.x ? x : y; }
struct node
{
    int Min, lazy;
    pii m1, m2, m3, m4;
    type a1, a2, a3; 
} Tree[maxn << 2];

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy += Tree[root].lazy;
    Tree[rson].lazy += Tree[root].lazy;
    Tree[lson].Min += Tree[root].lazy;
    Tree[rson].Min += Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void PushUp(int root)
{
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);

    Tree[root].m1 = Tree[lson].m1 + Tree[rson].m1;
    Tree[root].m2 = Tree[lson].m2 + Tree[rson].m2;
    Tree[root].a1 = Tree[lson].a1 + Tree[rson].a1 + Tree[lson].m1 * Tree[rson].m2;

    // m3 前缀最小A
    // m4 后缀最小B
    
    if ( Tree[lson].Min < Tree[rson].Min ) 
    {
        Tree[root].m3 = Tree[lson].m3;
        Tree[root].m4 = Tree[lson].m4 + Tree[rson].m2;
        Tree[root].a2 = Tree[lson].a2 + Tree[rson].a3 + Tree[lson].m4 * Tree[rson].m1;
    }
    else if ( Tree[lson].Min > Tree[rson].Min ) 
    {
        Tree[root].m3 = Tree[lson].m1 + Tree[rson].m3;
        Tree[root].m4 = Tree[rson].m4;
        Tree[root].a2 = Tree[lson].a3 + Tree[rson].a2 + Tree[lson].m2 * Tree[rson].m3;
    }
    else 
    {
        Tree[root].m3 = Tree[lson].m3;
        Tree[root].m4 = Tree[rson].m4;
        Tree[root].a2 = Tree[lson].a2 + Tree[rson].a2 + Tree[lson].m4 * Tree[rson].m3;
    }

    Tree[root].a3 = Tree[lson].a3 + Tree[rson].a3 + Tree[lson].m2 * Tree[rson].m1;
}

inline void Build(int root, int l, int r)
{
    Tree[root].m1 = Tree[root].m2 = Tree[root].m3 = Tree[root].m4 = pii(INF, 0);
    Tree[root].a1 = Tree[root].a2 = Tree[root].a3 = type(0, 0, INF);
    if ( l == r ) 
    {
        if ( l & 1 ) Tree[root].m1 = pii(A[(l + 1) / 2], l);
        else Tree[root].m2 = pii(B[l / 2], l);
        return ;
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) { Tree[root].lazy += val; Tree[root].Min += val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int pos)
{
    if ( l == r ) 
    {
        Tree[root].m1 = Tree[root].m2 = pii(INF, l);
        Tree[root].a1 = type(l, l, INF);
        return ;
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify2(lson, l, Mid, pos);
    else Modify2(rson, Mid + 1, r, pos);
    PushUp(root);
}

inline void print(int root, int l, int r)
{
    PushDown(root);
    printf("%lld %lld %lld\n", root, l, r);
    printf("%lld %lld %lld ", Tree[root].Min, Tree[root].m1.y, Tree[root].m2.y);
    printf("%lld %lld\n", Tree[root].m3.y, Tree[root].m4.y);
    printf("%lld %lld %lld\n", Tree[root].a1.a, Tree[root].a1.b, Tree[root].a1.sum);
    printf("%lld %lld %lld\n", Tree[root].a2.a, Tree[root].a2.b, Tree[root].a2.sum);
    printf("%lld %lld %lld\n", Tree[root].a3.a, Tree[root].a3.b, Tree[root].a3.sum);
    puts("");
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    print(lson, l, Mid);
    print(rson, Mid + 1, r);
}

signed main()
{
    freopen("disk.in", "r", stdin);
    freopen("disk.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &A[i]);
    REP(i, 1, n) scanf("%lld", &B[i]);
    Build(1, 1, 2 * n);    
    REP(i, 1, k)
    {
        type x = Tree[1].a2; int val = 1;
        if ( x.sum < Tree[1].a1.sum ) val = -1;
        else x = Tree[1].a1; 
        ans += x.sum;
        // printf("%lld\n", Tree[1].Min);
        // printf("%lld %lld %lld %lld\n", x.a, x.b, x.sum, val);

        // if ( i == 3 ) print(1, 1, 2 * n); 

        Modify1(1, 1, 2 * n, x.a, x.b - 1, val);
        Modify2(1, 1, 2 * n, x.a);
        Modify2(1, 1, 2 * n, x.b);
    }
    printf("%lld\n", ans);
    return 0;
}

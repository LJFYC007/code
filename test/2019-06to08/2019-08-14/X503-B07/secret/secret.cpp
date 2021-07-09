/***************************************************************
	File name: secret.cpp
	Author: ljfcnyali
	Create time: 2019年08月14日 星期三 19时07分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 600010;
const LL Mod = 998244353;

int n, m, w[maxn], dis, sum;
LL A[maxn][20], B[maxn][20], ans, p[maxn];

struct node
{
    LL a, b;
    int dep, lazy;
} Tree[maxn << 4];

inline LL power(LL a, LL b)
{
    LL r = 1; 
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod; b >>= 1;
    }
    return r;
}

inline LL inv(LL x) { return power(x, Mod - 2); }

inline void Push_up(int root)
{
    Tree[root].a = (Tree[lson].a * Tree[rson].a) % Mod;
    Tree[root].b = (Tree[lson].b * Tree[rson].a + Tree[rson].b) % Mod;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].a = inv(p[l]); Tree[root].b = (w[l] * Tree[root].a) % Mod; return ; }
    int Mid = l + r >> 1;
    Tree[lson].dep = Tree[rson].dep = Tree[root].dep - 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Push_up(root);
}

inline void Push_down(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy = Tree[rson].lazy = Tree[root].lazy;
    Tree[lson].a = A[Tree[root].lazy][Tree[lson].dep]; 
    Tree[rson].a = Tree[lson].a;
    Tree[lson].b = B[Tree[root].lazy][Tree[lson].dep];
    Tree[rson].b = Tree[lson].b;
    Tree[root].lazy = 0;
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        ans = ((ans * Tree[root].a) + Tree[root].b) % Mod;
        return ;
    }
    Push_down(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

inline void Update(int root, int l, int r, int L, int R, int s)
{
    if ( L <= l && r <= R ) 
    {
        Tree[root].a = A[s][Tree[root].dep]; Tree[root].b = B[s][Tree[root].dep];
        Tree[root].lazy = s;
        return ;
    }
    Push_down(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Update(lson, l, Mid, L, R, s);
    if ( Mid < R ) Update(rson, Mid + 1, r, L, R, s);
    Push_up(root);
}

signed main()
{
    freopen("secret.in", "r", stdin);
    freopen("secret.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%lld", &p[i]);
    REP(i, 1, n) scanf("%d", &w[i]);
    for ( int j = 18; j >= 0; -- j ) if ( n >= (1 << j) ) { dis = j + 1; n = 1 << (j + 1); break ; }
    Tree[1].dep = dis; Build(1, 1, n);
    REP(o, 1, m)
    {
        int opt, l, r, x, y; scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 1 ) 
        {
            ans = 0;
            Query(1, 1, n, l, r);
            printf("%lld\n", ans);
        }
        else
        {
            LL x, y; scanf("%lld%lld", &x, &y);
            A[++ sum][0] = inv(x); 
            B[sum][0] = (y * A[sum][0]) % Mod;
            REP(i, 1, dis) 
            { 
                A[sum][i] = power(A[sum][0], 1 << i); 
                B[sum][i] = (B[sum][i - 1] * A[sum][i - 1] + B[sum][i - 1]) % Mod; 
            }
            Update(1, 1, n, l, r, sum);
        }
    }
    return 0;
}

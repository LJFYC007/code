/***************************************************************
	File name: easy.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 10时34分49秒
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

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], g[maxn][19], Root[maxn], tot;
struct node { int lson, rson, lazy, sum; } Tree[maxn << 7];

inline int power(int a, int b) 
{ 
    if ( a == 1 ) return 1; 
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = (LL)r * a % Mod; a = (LL)a * a % Mod; b >>= 1; } 
    return r; 
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) { root = ++ tot; Tree[root].lazy = Tree[root].sum = 1; }
    Tree[root].sum = (LL)Tree[root].sum * power(val, R - L + 1) % Mod;
    if ( L == l && r == R ) { Tree[root].lazy = (LL)Tree[root].lazy * val % Mod; return ; }
    int Mid = l + r >> 1;
    if ( R <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    else if ( Mid < L ) Modify(rs(root), Mid + 1, r, L, R, val);
    else
    {
        Modify(ls(root), l, Mid, L, Mid, val);
        Modify(rs(root), Mid + 1, r, Mid + 1, R, val);
    }
}

inline int Query(int root, int l, int r, int L, int R, int x)
{
    if ( !root ) return 1;
    if ( L == l && r == R ) return (LL)Tree[root].sum * power(x, r - l + 1) % Mod;
    int Mid = l + r >> 1; x = (LL)x * Tree[root].lazy % Mod;
    if ( R <= Mid ) return Query(ls(root), l, Mid, L, R, x);
    if ( Mid < L ) return Query(rs(root), Mid + 1, r, L, R, x);
    return (LL)Query(ls(root), l, Mid, L, Mid, x) * Query(rs(root), Mid + 1, r, Mid + 1, R, x) % Mod;
}

inline int lowbit(int x) { return x & -x; }

inline void Modify1(int pos, int l, int r, int val)
{
    for ( int i = pos; i <= n; i += lowbit(i) ) Modify(Root[i], 1, n, l, r, val);
}

inline int Query1(int pos, int l, int r)
{
    if ( pos == 0 ) return 1;
    int ret = 1;
    for ( int i = pos; i > 0; i -= lowbit(i) ) ret = (LL)ret * Query(Root[i], 1, n, l, r, 1) % Mod;
    return ret;
}

signed main()
{
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) g[i][0] = a[i];
    REP(j, 1, 18) REP(i, 1, n) if ( i + (1 << j - 1) <= n ) g[i][j] = __gcd(g[i][j - 1], g[i + (1 << j - 1)][j - 1]);
    REP(i, 1, n)
    {
        int x = a[i], l = i;
        while ( x != 1 && l <= n ) 
        {
            int r = l;
            for ( int j = 18; j >= 0; -- j ) if ( r + (1 << j) <= n && g[r + 1][j] % x == 0 ) r += 1 << j;
            Modify1(i, l, r, x);
            l = r + 1; x = __gcd(x, a[l]);
        }
    }
    while ( m -- ) 
    {
        int l, r; scanf("%d%d", &l, &r);
        int ret = Query1(r, l, r) * (LL)power(Query1(l - 1, l, r), Mod - 2) % Mod;
        printf("%d\n", ret);
    }
    return 0;
}

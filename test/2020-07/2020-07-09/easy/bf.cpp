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
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], g[maxn][18], Root[maxn], tot;
struct node { int lson, rson, lazy, sum; } Tree[maxn << 5];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void PushTag(int root, int l, int r, int val)
{
    Tree[root].lazy = Tree[root].lazy * val % Mod;
    Tree[root].sum = Tree[root].sum * power(val, r - l + 1) % Mod;
}

inline void PushDown(int root, int l, int r)
{
    if ( Tree[root].lazy == 1 ) return ;
    int Mid = l + r >> 1;
    if ( !ls(root) ) { ls(root) = ++ tot; Tree[ls(root)].sum = Tree[ls(root)].lazy = 1; }
    if ( !rs(root) ) { rs(root) = ++ tot; Tree[rs(root)].sum = Tree[rs(root)].lazy = 1; }
    PushTag(ls(root), l, Mid, Tree[root].lazy);
    PushTag(rs(root), Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = 1;
}

inline void PushUp(int root) { Tree[root].sum = Tree[ls(root)].sum * Tree[rs(root)].sum % Mod; }

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) { root = ++ tot; Tree[root].sum = Tree[root].lazy = 1; }
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 1;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 1; PushDown(root, l, r);
    if ( L <= Mid ) ret = ret * Query(ls(root), l, Mid, L, R) % Mod;
    if ( Mid < R ) ret = ret * Query(rs(root), Mid + 1, r, L, R) % Mod;
    return ret;
}

signed main()
{
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) g[i][0] = a[i];
    REP(j, 1, 17) REP(i, 1, n) if ( i + (1 << j - 1) <= n ) g[i][j] = __gcd(g[i][j - 1], g[i + (1 << j - 1)][j - 1]);
    Tree[0].sum = 1;
    REP(i, 1, n)
    {
        int x = a[i], l = i;
        while ( x != 1 && l <= n ) 
        {
            int r = l;
            for ( int j = 17; j >= 0; -- j ) if ( r + (1 << j) <= n && g[r + 1][j] % x == 0 ) r += 1 << j;
            Modify(Root[i], 1, n, l, r, x);
            l = r + 1; x = __gcd(x, a[l]);
        }
    }
    while ( m -- ) 
    {
        int l, r; scanf("%lld%lld", &l, &r);
        int ret = 1;
        REP(i, l, r) ret = ret * Query(Root[i], 1, n, l, r) % Mod;
        printf("%lld\n", ret);
    }
    return 0;
}

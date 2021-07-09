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
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], g[maxn][19], ans[maxn];
struct node { int lazy, sum; } Tree[maxn << 2];
vector<pii> Q[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = (LL)r * a % Mod; a = (LL)a * a % Mod; b >>= 1; } return r; }

inline void PushTag(int root, int l, int r, int val)
{
    Tree[root].lazy = (LL)Tree[root].lazy * val % Mod;
    Tree[root].sum = (LL)Tree[root].sum * power(val, r - l + 1) % Mod;
}

inline void PushDown(int root, int l, int r)
{
    if ( Tree[root].lazy == 1 ) return ;
    int Mid = l + r >> 1;
    PushTag(lson, l, Mid, Tree[root].lazy);
    PushTag(rson, Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = 1;
}

inline void PushUp(int root) { Tree[root].sum = (LL)Tree[lson].sum * Tree[rson].sum % Mod; }

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 1; PushDown(root, l, r);
    if ( L <= Mid ) ret = ret * Query(lson, l, Mid, L, R) % Mod;
    if ( Mid < R ) ret = (LL)ret * Query(rson, Mid + 1, r, L, R) % Mod;
    return ret;
}

signed main()
{
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) { int l, r;  scanf("%d%d", &l, &r); Q[l].push_back(pii(r, i)); }
    
    REP(i, 1, n * 4) Tree[i].lazy = Tree[i].sum = 1;
    REP(i, 1, n) g[i][0] = a[i];
    REP(j, 1, 18) REP(i, 1, n) if ( i + (1 << j - 1) <= n ) g[i][j] = __gcd(g[i][j - 1], g[i + (1 << j - 1)][j - 1]);
    for ( int i = n; i >= 1; -- i ) 
    {
        int x = a[i], l = i;
        while ( x != 1 && l <= n ) 
        {
            int r = l;
            for ( int j = 18; j >= 0; -- j ) if ( r + (1 << j) <= n && g[r + 1][j] % x == 0 ) r += 1 << j;
            Modify(1, 1, n, l, r, x);
            l = r + 1; x = __gcd(x, a[l]);
        }
        for ( auto it : Q[i] ) 
            ans[it.second] = Query(1, 1, n, 1, it.first);
    }

    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}

/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 15时49分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 100010;
const int Mod = 1e9 + 7;

int n, a[maxn], Map[maxn], ans, sum, Root[maxn], tot;
struct node { int lson, rson, sum[4]; } Tree[maxn << 6];

inline void Modify(int &root, int l, int r, int pos, int val, int opt)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) { Tree[root].sum[opt] += val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val, opt);
    else Modify(rs(root), Mid + 1, r, pos, val, opt);
    Tree[root].sum[opt] = (Tree[ls(root)].sum[opt] + Tree[rs(root)].sum[opt]) % Mod;
}

inline int Query(int root, int l, int r, int L, int R, int opt)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum[opt];
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R, opt);
    if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R, opt);
    return ret % Mod;
}

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int x, int y, int opt)
{
    for ( int i = pos; i <= n; i += lowbit(i) ) Modify(Root[i], 1, n, x, y, opt);
}

inline int Solve(int l, int r, int L, int R, int opt)
{
    int ret = 0;
    for ( int i = l; i > 0; i -= lowbit(i) ) 
        ret -= Query(Root[i], 1, n, L, R, opt + 2) - Query(Root[i], 1, n, L, R, opt) * l;
    for ( int i = r; i > 0; i -= lowbit(i) ) 
        ret += Query(Root[i], 1, n, L, R, opt + 2) - Query(Root[i], 1, n, L, R, opt) * l;
    return ret % Mod;
}

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n)
    {
        int j = Map[a[i]]; 
        sum += (i - j) * a[i];
        sum += Solve(j, i, 1, a[i], 0) * a[i];
        sum += Solve(j, i, a[i], n, 1);
        ans += sum;
        if ( j ) 
        {
            add(j, a[i], -1, 0); add(j, a[i], -a[i], 1); 
            add(j, a[i], -j, 2); add(j, a[i], -j * a[i], 3);
        }
        Map[a[i]] = i;
        add(i, a[i], 1, 0); add(i, a[i], a[i], 1); 
        add(i, a[i], i, 2); add(i, a[i], i * a[i], 3);
        sum %= Mod;
    }
    ans %= Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

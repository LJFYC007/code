/***************************************************************
	File name: gift.cpp
	Author: ljfcnyali
	Create time: 2020年11月01日 星期日 11时32分10秒
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

const int maxn = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, a[maxn], Root[2][maxn], ans, lst[maxn], tot;
struct node { int lson, rson, lazy, sum; } Tree[maxn * 80];

inline void PushTag(int &root, int l, int r, int val)
{
    if ( !root ) root = ++ tot;
    Tree[root].lazy += val;
    Tree[root].sum = (Tree[root].sum + (r - l + 1) * val) % Mod;
}

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].lazy ) return ;
    int Mid = l + r >> 1;
    PushTag(ls(root), l, Mid, Tree[root].lazy);
    PushTag(rs(root), Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify2(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify2(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify2(rs(root), Mid + 1, r, L, R, val);
    Tree[root].sum = (Tree[ls(root)].sum + Tree[rs(root)].sum) % Mod;
}

inline int Query2(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root, l, r);
    if ( L <= Mid ) ret += Query2(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query2(rs(root), Mid + 1, r, L, R);
    return ret % Mod;
}

inline int lowbit(int x) { return x & -x; }

inline void Modify1(int op, int pos, int l, int r, int val)
{
    for ( int i = pos; i <= n; i += lowbit(i) ) 
        Modify2(Root[op][i], 1, n, l, r, val);
}

inline int Query1(int op, int pos, int l, int r)
{
    int ret = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) 
        ret = (ret + Query2(Root[op][i], 1, n, l, r)) % Mod;
    return ret;
}

signed main()
{
    freopen("gift.in", "r", stdin);
    freopen("gift.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    int sum = 0, num = 0;
    REP(i, 1, n)
    {
        int x = lst[a[i]] + 1; lst[a[i]] = i;
        Modify1(0, a[i], x, i, 1); Modify1(1, n - a[i] + 1, x, i, a[i]);
        sum = (sum + Query1(0, a[i], x, i) * a[i] + Query1(1, n - a[i], x, i)) % Mod;
        ans = (ans + sum) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

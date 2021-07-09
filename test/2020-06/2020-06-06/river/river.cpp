/***************************************************************
	File name: river.cpp
	Author: ljfcnyali
	Create time: 2020年06月06日 星期六 09时31分17秒
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

const int maxn = 1e6 + 10;

int n, m, a[maxn], f[maxn], g[maxn], dfn[maxn], ans;
struct node { int Min, lazy, pos; } Tree[maxn << 2];
bool flag = false;

inline void PushUp(int root)
{
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    if ( Tree[lson].Min < Tree[rson].Min ) Tree[root].pos = Tree[lson].pos;
    else Tree[root].pos = Tree[rson].pos;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    Tree[lson].lazy += x; Tree[lson].Min += x;
    Tree[rson].lazy += x; Tree[rson].Min += x;
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) 
    { 
        Tree[root].Min = val;
        Tree[root].pos = l;
        return ;
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 0, m - 1) { scanf("%lld", &a[i]); Modify(1, 0, m - 1, i, a[i] + i); }
    REP(i, 0, m - 1)
    {
        g[i] = (Tree[1].pos - i + m) % m;
        -- Tree[1].lazy; -- Tree[1].Min;
        Modify(1, 0, m - 1, i, a[i] + m - 1);
    }
    REP(i, 1, n) 
    {
        f[i] = f[i - 1] + g[f[i - 1] % m] + a[(f[i - 1] + g[f[i - 1] % m]) % m];
        if ( dfn[f[i] % m] ) 
        {
            int tmp = i - dfn[f[i] % m], lst = dfn[f[i] % m];
            n -= lst - 1;
            ans = f[i - 1] + (f[i] - f[lst]) * ((n / tmp) - 1);
            n %= tmp;
            f[0] = ans; flag = true; break ; 
        }
        dfn[f[i] % m] = i;
    }
    if ( flag == false ) { printf("%lld\n", f[n]); return 0; }
    REP(i, 1, n) f[i] = f[i - 1] + g[f[i - 1] % m] + a[(f[i - 1] + g[f[i - 1] % m]) % m];
    printf("%lld\n", f[n]);
    return 0;
}

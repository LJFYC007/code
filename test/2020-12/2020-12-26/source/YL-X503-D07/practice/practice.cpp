/***************************************************************
	File name: practice.cpp
	Author: ljfcnyali
	Create time: 2020年12月28日 星期一 20时45分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], t[4][4], fac[maxn], now, ans;
struct node { int val[4], pos[4], len; } Tree[maxn << 2];

inline void PushUp(int root)
{
    REP(i, 1, 3)
    {
        int j = Tree[rson].pos[i], val = Tree[rson].val[i] * fac[Tree[lson].len] % Mod;
        Tree[root].pos[i] = Tree[lson].pos[j];
        Tree[root].val[i] = (val + Tree[lson].val[j]) % Mod;
    }
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) 
    {
        REP(i, 1, 3) { Tree[root].pos[i] = t[i][val]; Tree[root].val[i] = i != val; }
        return ; 
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) 
    {
        ans = (ans * fac[Tree[root].len] + Tree[root].val[now]) % Mod;
        now = Tree[root].pos[now]; return ;
    }
    int Mid = l + r >> 1;
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
}

signed main()
{
    freopen("practice.in", "r", stdin);
    freopen("practice.out", "w", stdout);
    REP(i, 1, 3) REP(j, 1, 3) REP(k, 1, 3) if ( i != k && j != k ) t[i][j] = k;
    REP(i, 1, 3) t[i][i] = i;
    scanf("%lld%lld", &n, &m); fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * 2 % Mod;
    REP(i, 1, n) { scanf("%lld", &a[i]); Modify(1, 1, n, i, a[i]); }
    while ( m -- ) 
    {
        int op, l, r; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) { Modify(1, 1, n, l, r); a[l] = r; }
        else 
        {
            ans = 0; now = a[r]; Query(1, 1, n, l, r - 1);
            printf("%lld\n", (ans + Mod) % Mod);
        }
    }
    return 0;
}

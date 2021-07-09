/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 19时57分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 1e9 + 7;
const int INF = 1e18;

int n, m, a[maxn], ans[maxn], suf[maxn], pre1[maxn], pre2[maxn], sum[maxn];
pii f[maxn], g[maxn];
struct node 
{ 
    int l, r, id; 
    node ( int a = 0, int b = 0, int c = 0 ) { l = a; r = b; id = c; } 
    bool operator < (const node &a) const { return l > a.l; }
} ;
vector<node> Q[maxn];
vector<int> ttt[maxn];
struct Node { int len[4], sum, lazy[4]; } Tree[maxn << 2];
// 0 -> len; 1 -> mn * mx; 2 -> mx; 3 -> mn; 

inline void add(int root, int l, int r, int L, int R, int id)
{
    if ( l > r ) return ;
    if ( L == l && r == R ) { ttt[root].push_back(id); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid && Mid <= R ) Q[root].push_back(node(L, R, id));
    if ( L < Mid ) add(lson, l, Mid - 1, L, min(R, Mid - 1), id);
    if ( Mid < R ) add(rson, Mid + 1, r, max(L, Mid + 1), R, id);
}

inline void PushTag(int root, int op, int val)
{
    Tree[root].sum = (Tree[root].sum + Tree[root].len[op] * val) % Mod;
    Tree[root].lazy[op] = (Tree[root].lazy[op] + val) % Mod;
}

inline void PushDown(int root)
{
    REP(i, 0, 3)
    {
        if ( !Tree[root].lazy[i] ) continue ;
        PushTag(lson, i, Tree[root].lazy[i]);
        PushTag(rson, i, Tree[root].lazy[i]);
        Tree[root].lazy[i] = 0;
    }
}

inline void Build(int root, int l, int r)
{
    Tree[root].sum = 0; REP(i, 0, 3) Tree[root].lazy[i] = 0;
    if ( l == r ) 
    {
        Tree[root].len[0] = 1; Tree[root].len[1] = suf[l];
        Tree[root].len[2] = pre1[l]; Tree[root].len[3] = pre2[l];
        return ;
    }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    REP(i, 0, 3) Tree[root].len[i] = (Tree[lson].len[i] + Tree[rson].len[i]) % Mod;
}

inline void Modify(int root, int l, int r, int L, int R, int op, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, op, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, op, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, op, val);
    Tree[root].sum = (Tree[lson].sum + Tree[rson].sum) % Mod;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret % Mod;
}

inline void Solve(int root, int l, int r)
{
    if ( l > r ) return ;
    int Mid = (l + r) >> 1; Solve(lson, l, Mid - 1); Solve(rson, Mid + 1, r);
    sum[root] = (sum[lson] + sum[rson]) % Mod;
    int n1 = 0, n2 = 0, pos1 = 1, pos2 = 1, Min = INF, Max = -INF;
    suf[Mid - 1] = pre1[Mid - 1] = pre2[Mid - 1] = 0;
    REP(i, Mid, r)
    {
        if ( !n1 || a[i] > f[n1].x ) f[++ n1] = pii(a[i], i);
        if ( !n2 || a[i] < g[n2].x ) g[++ n2] = pii(a[i], i);
        suf[i] = f[n1].x * g[n2].x % Mod;
        pre1[i] = f[n1].x; pre2[i] = g[n2].x;
    }
    f[++ n1] = pii(INF, r + 1); g[++ n2] = pii(-INF, r + 1);
    Build(1, Mid, r);
    REP(i, Mid, r) 
    { 
        suf[i] = (suf[i - 1] + suf[i]) % Mod; 
        pre1[i] = (pre1[i - 1] + pre1[i]) % Mod; 
        pre2[i] = (pre2[i - 1] + pre2[i]) % Mod; 
    }
    sort(Q[root].begin(), Q[root].end());
    int now = 0;
    for ( int i = Mid; i >= l; -- i ) 
    {
        Min = min(Min, a[i]); Max = max(Max, a[i]);
        while ( pos1 <= n1 && Max > f[pos1].x ) ++ pos1;
        while ( pos2 <= n2 && Min < g[pos2].x ) ++ pos2;

        int x1 = f[pos1].y, x2 = g[pos2].y;
        int posx = min(x1 - 1, x2 - 1);
        if ( posx >= Mid ) 
        {
            sum[root] = (sum[root] + (Max * Min % Mod) * (posx - Mid + 1)) % Mod;
            Modify(1, Mid, r, Mid, posx, 0, Max * Min % Mod);
        }
        int posy = max(x1, x2);
        if ( posy <= r ) 
        {
            sum[root] = (sum[root] + suf[r] - suf[posy - 1]) % Mod;
            Modify(1, Mid, r, posy, r, 1, 1);
        }
        if ( x1 < x2 ) 
        {
            sum[root] = (sum[root] + Min * (pre1[x2 - 1] - pre1[x1 - 1])) % Mod;
            Modify(1, Mid, r, x1, x2 - 1, 2, Min);
        }
        if ( x1 > x2 ) 
        {
            sum[root] = (sum[root] + Max * (pre2[x1 - 1] - pre2[x2 - 1])) % Mod;
            Modify(1, Mid, r, x2, x1 - 1, 3, Max);
        }

        while ( now < Q[root].size() && Q[root][now].l == i ) 
        {
            ans[Q[root][now].id] = (ans[Q[root][now].id] + Query(1, Mid, r, Mid, Q[root][now].r)) % Mod;
            ++ now;
        }
    }
    for ( auto it : ttt[root] ) ans[it] = (ans[it] + sum[root]) % Mod;
}

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, m)
    {
        int l, r; scanf("%lld%lld", &l, &r); 
        add(1, 1, n, l, r, i);
    }
    Solve(1, 1, n);
    REP(i, 1, m) printf("%lld\n", (ans[i] + Mod) % Mod);
    return 0;
}

/***************************************************************
	File name: milktea.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 09时24分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, k, a[maxn], belong[maxn], Block, HaHa[maxn], tot; 
LL h[maxn], f[maxn], ans[maxn], b[maxn], c[2][maxn], Map[maxn];
struct data 
{ 
    int l, r, id, val; 
    data(int a = 0, int b = 0, int c = 0, int d = 0) { l = a; r = b; id = c; val = d; }
    bool operator < (const data &a) const { return l < a.l; }
} ;
vector<data> g[maxn], p[maxn];
struct NODE { int op, l, r, val; } Q[maxn];
struct node { int lazy, len; LL sum; } Tree[maxn << 2];

inline int lowbit(int x) { return x & -x; }

inline void add(int op, int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[op][i] += val; }

inline LL get(int op, int pos) { LL ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[op][i]; return ret; }

inline LL Get(int pos) 
{
    LL ret = (pos + 1) * get(0, pos) - get(1, pos);
    return ret;
}

inline void PushTag(int root, int val) { Tree[root].sum += 1ll * Tree[root].len * val; Tree[root].lazy += val; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = r - l + 1; Tree[root].lazy = 0;
    if ( l == r ) { Tree[root].sum = a[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline LL Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1; LL ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

signed main()
{
    freopen("milktea.in", "r", stdin);
    freopen("milktea.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) scanf("%d", &a[i]);
    Build(1, 1, n);
    REP(i, 1, m) 
    { 
        scanf("%d%d%d", &Q[i].op, &Q[i].l, &Q[i].r); 
        if ( Q[i].op == 1 ) { scanf("%d", &Q[i].val); Modify(1, 1, n, Q[i].l, Q[i].r, Q[i].val); }
        else h[i] = Query(1, 1, n, Q[i].l, Q[i].r);
        h[i] += h[i - 1];
    }
    Block = sqrt(m) / 2 + 1;
    REP(i, 1, m) belong[i] = (i - 1) / Block + 1;
    REP(i, 1, k) 
    { 
        int l, r, t; scanf("%d%d", &l, &r); t = belong[l] - 1; 
        ans[i] = h[r] - h[l - 1];
        int L = t * Block + 1, R = l - 1;
        g[l - 1].push_back(data(L, R, i, 1));
        g[r].push_back(data(L, R, i, -1));
        p[t].push_back(data(l, r, i, -1));
    }

    for ( int l = 1, r = Block; l <= m; l += Block, r = min(m, r + Block) )
    {
        REP(i, 1, n) b[i] = 0;
        REP(i, l, r) if ( Q[i].op == 1 ) { b[Q[i].l] += Q[i].val; b[Q[i].r + 1] -= Q[i].val; }
        REP(i, 1, n) { b[i] += b[i - 1]; c[0][i] += b[i]; c[1][i] = c[1][i - 1] + c[0][i]; }
        REP(i, 1, m)
        {
            f[i] = f[i - 1];
            if ( Q[i].op == 2 ) f[i] += c[1][Q[i].r] - c[1][Q[i].l - 1];
        }
        for ( int i = 0; i < p[belong[l]].size(); ++ i ) 
        {
            data x = p[belong[l]][i];
            ans[x.id] += (f[x.r] - f[x.l - 1]) * x.val;
        }
    }

    mem(c); memset(Map, -1, sizeof(Map));
    REP(i, 1, m)
    {
        tot = 0;
        if ( Q[i].op == 2 ) 
        {
            add(0, Q[i].l, 1); add(0, Q[i].r + 1, -1);
            add(1, Q[i].l, Q[i].l); add(1, Q[i].r + 1, -Q[i].r - 1);
        }
        for ( int o = 0; o < g[i].size(); ++ o ) 
        {
            LL ret = 0;
            REP(j, g[i][o].l, g[i][o].r) 
            {
                if ( Q[j].op == 2 ) continue ;
                if ( Map[j] != -1 ) ret += Map[j];
                else 
                { 
                    LL x = (Get(Q[j].r) - Get(Q[j].l - 1)) * Q[j].val;
                    HaHa[++ tot] = j; ret += x; Map[j] = x; 
                }
            }
            ans[g[i][o].id] += ret * g[i][o].val;
        }
        REP(o, 0, tot) Map[HaHa[o]] = -1;
    }
    REP(i, 1, k) printf("%lld\n", ans[i]);
    return 0;
}

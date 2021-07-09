/***************************************************************
	File name: P3527.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 19时11分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 300010;

int n, m, k, ans[maxn], c[maxn], C[maxn];
vector<int> a[maxn];

struct node1
{
    int l, r, w;
} q[maxn];

struct node2
{
    int id, val;
} p[maxn], b[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int val)
{
    for ( int i = x; i <= m; i += lowbit(i) ) c[i] += val, C[i] += val * x; 
}

inline int Get_Sum(int x)
{
    int sum = 0;
    for ( int i = x; i > 0; i -= lowbit(i) ) sum += (x + 1) * c[i] - C[i];
    return sum;
}

inline void Solve(int l, int r, int L, int R) 
{
    if ( l == r ) { REP(i, L, R) ans[p[i].id] = l; return ; }
    int Mid = l + r >> 1;
    REP(i, l, Mid)
    {
        if ( q[i].l <= q[i].r ) { add(q[i].l, q[i].w); add(q[i].r + 1, -q[i].w); continue ; }
        add(q[i].l, q[i].w); add(1, q[i].w); add(q[i].r + 1, -q[i].w);
    }
    int ll = L, rr = R;
    REP(i, ll, rr)
    {
        int x = 0;
        REP(j, 0, a[p[i].id].size() - 1) { x += Get_Sum(a[p[i].id][j]) - Get_Sum(a[p[i].id][j] - 1); if ( x >= p[i].val ) break ; }
        if ( x >= p[i].val ) b[L ++] = p[i];
        else { p[i].val -= x; b[R --] = p[i]; }
    }
    REP(i, ll, rr) p[i] = b[i];
    REP(i, l, Mid)
    {
        if ( q[i].l <= q[i].r ) { add(q[i].l, -q[i].w); add(q[i].r + 1, q[i].w); continue ; }
        add(q[i].l, -q[i].w); add(1, -q[i].w); add(q[i].r + 1, q[i].w);
    }
    Solve(l, Mid, ll, L - 1); Solve(Mid + 1, r, R + 1, rr);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) { int x; scanf("%lld", &x); a[x].push_back(i); }
    REP(i, 1, n) scanf("%lld", &p[i].val), p[i].id = i; 
    scanf("%lld", &k);
    REP(i, 1, k) scanf("%lld%lld%lld", &q[i].l, &q[i].r, &q[i].w);
    Solve(1, k + 1, 1, n);
    REP(i, 1, n) if ( ans[i] != k + 1) printf("%lld\n", ans[i]); else puts("NIE");
    return 0;
}

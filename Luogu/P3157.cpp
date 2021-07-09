/***************************************************************
	File name: P3157.cpp
	Author: ljfcnyali
	Create time: 2019年07月12日 星期五 09时04分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

int c[maxn], n, m, id[maxn];
LL ans;

struct node
{
    int t, val; LL ans;
} a[maxn];

inline int cmp1(node a, node b) { return a.val > b.val; }

inline int cmp2(node a, node b) { return a.val < b.val; }

inline int cmp3(node a, node b) { return a.t > b.t; }

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int val) { for ( int i = x; i <= n + 1; i += lowbit(i) ) c[i] += val; }

inline int query(int x) { int s = 0; for ( int i = x; i > 0; i -= lowbit(i) ) s += c[i]; return s; }

inline void CDQ(int l, int r)
{
    if ( l == r ) return; int Mid = l + r >> 1;
    CDQ(l, Mid); CDQ(Mid + 1, r);
    sort(a + l, a + Mid + 1, cmp1); sort(a + Mid + 1, a + r + 1, cmp1);
    int i = Mid + 1, j = l;
    while ( i <= r ) 
    {
        while ( a[j].val > a[i].val && j <= Mid ) add(a[j ++].t, 1);
        a[i].ans += query(a[i].t);
        ++ i;
    }
    REP(i, l, j - 1) add(a[i].t, -1);
    sort(a + l, a + Mid + 1, cmp2); sort(a + Mid + 1, a + r + 1, cmp2);
    i = l; j = Mid + 1;
    while ( i <= Mid ) 
    {
        while ( a[i].val > a[j].val && j <= r ) add(a[j ++].t, 1);
        a[i].ans += query(a[i].t);
        ++ i;
    }
    REP(i, Mid + 1, j - 1) add(a[i].t, -1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].ans = 0; a[i].t = 1; id[a[i].val] = i; }
    REP(i, 1, m) { int x; scanf("%d", &x); a[id[x]].t = m - i + 1; }
    REP(i, 1, n) { ans += query(n + 1) - query(a[i].val); add(a[i].val, 1); }
    REP(i, 1, n) add(a[i].val, -1);
    CDQ(1, n);
    sort(a + 1, a + n + 1, cmp3);
    REP(i, 1, m) { printf("%lld\n", ans); ans -= a[i].ans; }
    return 0;
}

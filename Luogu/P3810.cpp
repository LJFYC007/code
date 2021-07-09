/***************************************************************
	File name: P3810.cpp
	Author: ljfcnyali
	Create time: 2019年07月10日 星期三 14时47分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

struct node
{
    LL a, b, c, w, ans;
} a[maxn], p[maxn];
inline LL cmp1(node a, node b) 
{ 
    return a.a < b.a || (a.a == b.a && (a.b < b.b || (a.b == b.b && a.c < b.c))); 
}

inline LL cmp2(node a, node b) { return a.b < b.b || (a.b == b.b && a.c < b.c); }

LL c[maxn], n, m, cnt, sum, ans[maxn];

inline LL lowbit(LL x) { return x & -x; }

inline void add(LL x, LL val) { for ( LL i = x; i <= m; i += lowbit(i) ) c[i] += val; }

inline LL query(LL x) { LL sum = 0; for ( LL i = x; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

inline void CDQ(LL l, LL r)
{
    if ( l == r ) return ;
    LL Mid = l + r >> 1; CDQ(l, Mid); CDQ(Mid + 1, r);
    LL i = Mid + 1, j = l;
    sort(p + l, p + Mid + 1, cmp2);
    sort(p + Mid + 1, p + r + 1, cmp2);
    while ( i <= r ) 
    {
        while ( p[j].b <= p[i].b && j <= Mid ) 
        {
            add(p[j].c, p[j].w); ++ j;
        }
        p[i].ans += query(p[i].c);
        ++ i;
    }
    REP(i, l, j - 1) add(p[i].c, -p[i].w);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld%lld%lld", &a[i].a, &a[i].b, &a[i].c);
    sort(a + 1, a + n + 1, cmp1);
    REP(i, 1, n)
    {
        ++ sum;
        if ( a[i].a != a[i + 1].a || a[i].b != a[i + 1].b || a[i].c != a[i + 1].c ) 
        {
            p[++ cnt] = a[i]; p[cnt].w = sum; sum = 0;
        }
    }
    CDQ(1, cnt);
    REP(i, 1, cnt) ans[p[i].ans + p[i].w - 1] += p[i].w;
    REP(i, 0, n - 1) printf("%lld\n", ans[i]);
    return 0;
}

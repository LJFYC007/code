/***************************************************************
	File name: P1972.cpp
	Author: ljfcnyali
	Create time: 2019年06月12日 星期三 15时35分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int a[maxn], c[maxn], n, m, last[maxn * 2], ans[maxn];

struct node
{
    int l, r, x;
} p[maxn];

inline int cmp(node a, node b)
{
    return a.r < b.r || (a.r == b.r && a.l < b.l);
}

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int val)
{
    for ( int i = x; i <= n; i += lowbit(i) ) c[i] += val;
}

inline int getsum(int x)
{
    int ans = 0;
    for ( int i = x; i >= 1; i -= lowbit(i) ) ans += c[i];
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    scanf("%d", &m);
    REP(i, 1, m) { scanf("%d%d", &p[i].l, &p[i].r); p[i].x = i; }
    sort ( p + 1, p + m + 1, cmp ) ;
    int now = 1;
    REP(i, 1, m)
    {
        REP(j, now, p[i].r)
        {
            if ( last[a[j]] ) add(last[a[j]], -1);
            add(j, 1); last[a[j]] = j;
        }
        now = p[i].r + 1;
        ans[p[i].x] = getsum(p[i].r) - getsum(p[i].l - 1);
    }
    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}

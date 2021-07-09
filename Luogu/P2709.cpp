/***************************************************************
	File name: P2709.cpp
	Author: ljfcnyali
	Create time: 2019年07月02日 星期二 09时19分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 50010;

int n, m, block, ans[maxn], a[maxn], sum, size[maxn];

struct node
{
    int l, r, id, p;
} q[maxn];

inline int cmp(node a, node b)
{
    return a.id < b.id || (a.id == b.id && a.r < b.r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int k = 0;
    scanf("%d%d%d", &n, &m, &k); block = sqrt(n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) { scanf("%d%d", &q[i].l, &q[i].r); q[i].id = (q[i].l - 1) / block + 1; q[i].p = i; }
    sort(q + 1, q + m + 1, cmp);
    int l = q[1].l, r = q[1].l - 1;    
    REP(i, 1, m)
    {
        while ( l < q[i].l ) { -- size[a[l]]; sum -= size[a[l]] * 2 + 1; ++ l; }
        while ( l > q[i].l ) { -- l; ++ size[a[l]]; sum += size[a[l]] * 2 - 1; }
        while ( r < q[i].r ) { ++ r; ++ size[a[r]]; sum += size[a[r]] * 2 - 1; }
        while ( r > q[i].r ) { -- size[a[r]]; sum -= size[a[r]] * 2 + 1; -- r; }
        ans[q[i].p] = sum;
//        printf("%d %d %d\n", sum, q[i].l, q[i].r);
    }
    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}

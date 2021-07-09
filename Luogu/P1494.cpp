/***************************************************************
	File name: P1494.cpp
	Author: ljfcnyali
	Create time: 2019年07月02日 星期二 12时58分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5000010;

struct node
{
    int l, r, id, p;
} q[maxn];

LL n, m, a[maxn], ans1[maxn], ans2[maxn], sum, block, size[maxn];

inline int cmp(node a, node b) { return a.id == b.id ? a.r < b.r : a.id < b.id; }

inline void Push_down(int x) { -- size[a[x]]; sum -= size[a[x]] * 2 + 1; }

inline void Push_up(int x) { ++ size[a[x]]; sum += size[a[x]] * 2 - 1; }

inline LL gcd(LL a, LL b) { if ( !b ) return a; return gcd(b, a % b); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]); 
    block = sqrt(n);
    REP(i, 1, m) { scanf("%lld%lld", &q[i].l, &q[i].r); q[i].id = (q[i].l - 1) / block + 1, q[i].p = i; }
//    REP(i, 1 ,m) cerr << q[i].l << " " << q[i].r << endl;
    sort(q + 1, q + m + 1, cmp);
    LL l = q[1].l, r = q[1].l - 1;
    REP(i, 1, m)
    {
        while ( l < q[i].l ) Push_down(l ++);
        while ( l > q[i].l ) Push_up(-- l);
        while ( r < q[i].r ) Push_up(++ r);
        while ( r > q[i].r ) Push_down(r --);
//        cerr << q[i].l << " " << q[i].r << " " << sum << endl;
        ans1[q[i].p] = sum - (r - l + 1);
        ans2[q[i].p] = (r - l + 1) * (r - l);
    }
    REP(i, 1, m)
    {
//        cerr << ans1[i] << " " << ans2[i] << endl;
        if ( ans1[i] == 0 ) { printf("0/1\n"); continue ; }
        LL t = gcd(ans1[i], ans2[i]);
        printf("%lld/%lld\n", ans1[i] / t, ans2[i] / t);
    }
    return 0;
}

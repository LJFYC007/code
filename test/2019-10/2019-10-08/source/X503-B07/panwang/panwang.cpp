/***************************************************************
	File name: panwang.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 18时54分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2000010;

int n, m1, m2;
struct node
{
    int val, num;
} a[maxn], b[maxn], c[maxn], d[maxn], e[maxn];

inline int Solve1()
{
    sort(a + 1, a + n + 1, [](const node &x, const node &y) { return x.val < y.val; });
    REP(i, 1, n) d[i] = a[i];
    int now = 1, ans = 0, sum = 0;
    REP(i, 1, n)
    {
        while ( b[now].val <= a[i].val && now <= m1 ) 
        {
            if ( b[now].num <= a[i].num ) { a[i].num -= b[now].num; b[now].num = 0; ++ now; continue ; }
            b[now].num -= a[i].num; a[i].num = 0; break ; 
        }
        ans += a[i].num * max(0ll, a[i].val);    
    }
    REP(i, 1, n) a[i] = d[i];
    if ( now <= m1 ) return 0;
    REP(i, 1, n) sum += a[i].num;
    now = 1;
    while ( sum && now <= m2 )
    {
        if ( c[now].val >= 0 ) break ;
        if ( c[now].num <= sum ) { ans -= c[now].num * c[now].val; sum -= c[now].num; ++ now; continue ; }
        ans -= sum * c[now].val; sum = 0;
    }
    return ans;
}

inline int Solve2()
{
    sort(a + 1, a + n + 1, [](const node &x, const node &y) { return x.val > y.val; });
    int now = 1, ans = 0;
    REP(i, 1, n)
    {
        while ( c[now].val <= a[i].val && now <= m2 ) 
        {
            if ( c[now].num <= a[i].num ) { ans += c[now].num * (a[i].val - c[now].val); a[i].num -= c[now].num; ++ now; continue ; }
            ans += a[i].num * (a[i].val - c[now].val);
            c[now].num -= a[i].num; a[i].num = 0; break ; 
        }
    }
    return ans;
}

signed main()
{
    freopen("panwang.in", "r", stdin);
    freopen("panwang.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m1, &m2);
    REP(i, 1, n) scanf("%lld%lld", &a[i].val, &a[i].num);
    REP(i, 1, m1) scanf("%lld%lld", &b[i].val, &b[i].num);
    REP(i, 1, m2) scanf("%lld%lld", &c[i].val, &c[i].num);
    sort(b + 1, b + m1 + 1, [](const node &x, const node &y) { return x.val < y.val; });
    sort(c + 1, c + m2 + 1, [](const node &x, const node &y) { return x.val < y.val; });
    int ans = Solve1();
    ans = max(ans, Solve2());
    printf("%lld\n", ans);
    return 0;
}

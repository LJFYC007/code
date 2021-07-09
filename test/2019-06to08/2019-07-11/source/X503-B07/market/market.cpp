/***************************************************************
	File name: market.cpp
	Author: ljfcnyali
	Create time: 2019年07月11日 星期四 09时14分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

LL dp[310][90010], n, m, ans[maxn];

struct node
{
    LL c, v, t;
    bool operator < (const node &a) const
    {
        return t < a.t;
    }
} a[maxn];

struct Node
{
    LL t, v, id;
    bool operator < (const Node &a) const
    {
        return t < a.t;
    }
} q[maxn];

int main()
{
    freopen("market.in", "r", stdin);
    freopen("market.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld%lld%lld", &a[i].c, &a[i].v, &a[i].t);
    sort(a + 1, a + n + 1);
//    REP(i, 1, n) printf("%lld %lld %lld\n", a[i].c, a[i].v, a[i].t);
    REP(i, 1, m) { scanf("%lld%lld", &q[i].t, &q[i].v); q[i].id = i; }
    sort(q + 1, q + m + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    LL now = 1, sum = 0;
    REP(i, 1, m)
    {
        REP(j, now, n)
        {
            if ( a[j].t > q[i].t ) break ; 
            sum += a[j].v;
            for ( LL k = sum; k >= 0; -- k )
            {
                dp[j][k] = min(dp[j - 1][k], dp[j][k + 1]);
                if ( k >= a[j].v ) 
                    dp[j][k] = min(dp[j][k], dp[j - 1][k - a[j].v] + a[j].c);
            }
            ++ now;
        }
        LL l = 1, r = sum; 
        while ( l <= r ) 
        {
            LL Mid = l + r >> 1;
            if ( dp[now - 1][Mid] <= q[i].v ) { ans[q[i].id] = Mid; l = Mid + 1; }
            else r = Mid - 1;
        }
    }
    //REP(i, 1, sum) printf("%lld ", dp[n][i]); puts("");
    REP(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}

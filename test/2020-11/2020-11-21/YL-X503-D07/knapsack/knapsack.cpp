/***************************************************************
	File name: knapsack.cpp
	Author: ljfcnyali
	Create time: 2020年11月21日 星期六 10时21分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, int>
typedef long long LL;

const int maxn = 50;

int n, q, a[maxn], m1, m2;
LL f[1 << 20], g[1 << 20], ans[510];
vector<pii> Q;

signed main()
{
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    scanf("%d%d", &n, &q); REP(i, 1, n) scanf("%d", &a[i]); 
    m1 = n / 2; m2 = n - m1;     
    REP(i, 0, (1 << m1) - 1) REP(j, 1, m1)
        if ( (i >> j - 1) & 1 ) f[i] += a[j];
    sort(f, f + (1 << m1));
    REP(i, 0, (1 << m2) - 1) REP(j, 1, m2)
        if ( (i >> j - 1) & 1 ) g[i] += a[m1 + j];
    sort(g, g + (1 << m2));
    REP(i, 1, q) { LL l, r; scanf("%lld%lld", &l, &r); Q.push_back(pii(l - 1, -i)); Q.push_back(pii(r, i)); }
    sort(Q.begin(), Q.end());

    for ( int i = 0; i < Q.size(); ++ i )
    {
        LL x = Q[i].first, sum = 0; int pos = (1 << m1) - 1;
        REP(j, 0, (1 << m2) - 1)
        {
            while ( pos >= 0 && f[pos] + g[j] > x ) -- pos;
            sum += pos + 1;
        }
        if ( Q[i].second > 0 ) ans[Q[i].second] += sum;
        else ans[-Q[i].second] -= sum;
    }

    REP(i, 1, q) printf("%lld\n", ans[i]);
    return 0;
}

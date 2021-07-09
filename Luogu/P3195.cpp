/***************************************************************
	File name: P3195.cpp
	Author: ljfcnyali
	Create time: 2020年06月17日 星期三 10时15分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, L, f[maxn], g[maxn], sum[maxn], tail, head;
pii Q[maxn];

inline double Slope(pii x, pii y) { return (x.first - y.first) * 1.0 / (x.second - y.second); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &L);
    REP(i, 1, n) { scanf("%lld", &sum[i]); sum[i] += sum[i - 1]; }
    REP(i, 1, n) sum[i] = sum[i] + i;
    head = tail = 1;
    REP(i, 1, n)
    {
        while ( head < tail && Slope(Q[head], Q[head + 1]) < 2 * sum[i] ) ++ head;
        
        f[i] = Q[head].first - 2 * sum[i] * Q[head].second + (L + 1) * (L + 1) - 2 * sum[i] * (L + 1) + sum[i] * sum[i];
        g[i] = f[i] + sum[i] * sum[i] + 2 * sum[i] * (L + 1);

        pii x = pii(g[i], sum[i]);
        while ( head < tail && Slope(Q[tail - 1], Q[tail]) > Slope(Q[tail - 1], x) ) -- tail;
        Q[++ tail] = x;
    }
    printf("%lld\n", f[n]);
    return 0;
}

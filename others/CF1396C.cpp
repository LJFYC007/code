/***************************************************************
	File name: CF1396C.cpp
	Author: ljfcnyali
	Create time: 2020年09月01日 星期二 22时07分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;

int n, r1, r2, r3, d, a[maxn], f[maxn], g[maxn], ans = INF;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld%lld", &n, &r1, &r2, &r3, &d);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) 
        f[i] = f[i - 1] + min(r1 * a[i] + r3 + d, min(r1 * (a[i] + 2), r2 + r1) + 3 * d + i);
    REP(i, 1, n) printf("%lld " ,f[i]); puts("");
    g[n + 1] = -d;
    for ( int i = n; i >= 1; -- i ) 
        g[i] = g[i + 1] + min(r1 * a[i] + r3 + d, min(r1 * (a[i] + 2), r2 + r1) + d + (i == n ? d + d : 0));
    REP(i, 1, n) ans = min(ans, f[i] + g[i + 1] + (n - i - 1) * d);
    printf("%lld\n", ans);
    return 0;
}

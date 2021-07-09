/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月05日 星期二 15时31分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 40;

int T, w, n, a[maxn], sum[maxn];
long double ans;

signed main()
{
    freopen("roulette.in", "r", stdin);
    freopen("roulette.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        mem(a); ans = 0;
        scanf("%lld%lld", &w, &n);
        REP(i, 1, n) scanf("%lld", &a[i]);
        n = 37;
        sort(a + 1, a + n + 1);
        REP(i, 1, n) sum[i] = sum[i - 1] + a[i];
        REP(i, 1, n - 2)
            REP(j, i, n - 1)
            {
                int ret = min(a[j + 1], (sum[j] + w + i) / j);
                if ( ret <= a[j] ) continue ;
                long double s = ((ret - 1) * i - sum[i]) * 36.0 / i;
                ans = max(ans, s - ret * (j - i) - (ret - 1) * i + sum[j]);
            }
        printf("%.7Lf\n", ans);
    }
    return 0;
}

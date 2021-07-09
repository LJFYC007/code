/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年10月11日 星期日 18时03分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;
const int INF = 1e18;

int n, k, l[maxn], r[maxn], a[maxn], f[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);     
    REP(i, 1, n) scanf("%lld%lld%lld", &l[i], &r[i], &a[i]);
    f[0] = 0; REP(i, 1, n) f[i] = INF; l[n + 1] = INF;
    REP(i, 0, n - 1)
    {
        int lst = 0, sum = f[i];
        REP(j, i + 1, n)
        {
            if ( lst > k ) break ; 
            int x = a[j] + lst, y = x, day = min(x / k, r[j] - l[j]);
            if ( k * (r[j] - l[j] + 1) < x ) break ; 
            x -= day * k; sum += day * k;
            if ( k * (r[j] - l[j]) >= y || r[j] < l[j + 1] ) 
            {
                // cout << y << " " << num << endl;
                // cout << i << " " << j << " " << sum << " " << x << endl;
                f[j] = min(f[j], sum + (x ? (j == n ? x : k) : 0));
            }
            lst = x;
        }
    }
    // REP(i, 1, n) printf("%lld ", f[i]); puts("");
    printf("%lld\n", f[n] == INF ? -1 : f[n]);
    return 0;
}

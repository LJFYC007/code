/***************************************************************
	File name: lost.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时21分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5e5 + 10;
const double INF = 1e18;

int n, c[maxn], f[maxn];

signed main()
{
    freopen("lost.in", "r", stdin);
    freopen("lost1.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &c[i]);
    REP(i, 2, n) scanf("%lld", &f[i]);
    REP(i, 2, n)
    {
        int x = f[i], len = 1;
        double ans = INF;
        while ( x ) 
        {
            ans = min(ans, (c[x] - c[i]) * 1.0 / len);
            x = f[x]; ++ len;
        }
        printf("%.7lf\n", ans);
    }
    return 0;
}

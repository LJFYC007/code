/***************************************************************
	File name: peng.cpp
	Author: ljfcnyali
	Create time: 2020年07月14日 星期二 10时50分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int INF = 1e18;

int n, m, t, ans, f[maxn][maxn], pre[maxn];
pii a[maxn];

signed main()
{
    freopen("peng.in", "r", stdin);
    freopen("peng1.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i].first); 
    REP(i, 1, m) { scanf("%lld", &a[i + n].first); a[i + n].second = 1; }
    t = n + m; sort(a + 1, a + t + 1);
    
    int delta = t; n = t;
    pre[1] = -1;
    REP(i, 2, n)
        if ( a[i].second == a[i - 1].second ) pre[i] = pre[i - 1];
        else pre[i] = i - 1;
    REP(i, 0, n) REP(j, 0, n + n) f[i][j] = INF;
    if ( a[1].second == 0 ) f[1][1 + delta] = 0;
    else f[1][-1 + delta] = 0;
    REP(i, 2, n) REP(j, -i + delta, i + delta)
    {
        int x = a[i - 1].second, y = a[i].second;
        if ( !a[i].second )
        {
            if ( j >= delta ) f[i][j + 1] = min(f[i][j + 1], f[i - 1][j] + abs(j - delta) * (a[i].first - a[i - 1].first));
            else REP(k, j + 1, delta) f[i][k] = min(f[i][k], f[i - 1][j] + abs(j - delta) * (a[i].first - a[i - 1].first));
        }
        else 
        {
            if ( j <= delta ) f[i][j - 1] = min(f[i][j - 1], f[i - 1][j] + abs(j - delta) * (a[i].first - a[i - 1].first));
            else REP(k, delta, j - 1) f[i][k] = min(f[i][k], f[i - 1][j] + abs(j - delta) * (a[i].first - a[i - 1].first));
        }
        if ( j == delta ) 
        {
            if ( y == 0 ) f[i][delta + 1] = min(f[i][delta + 1], f[i - 1][j]);
            else f[i][delta - 1] = min(f[i][delta - 1], f[i - 1][j]);
            f[i][delta] = min(f[i][delta], f[i - 1][j] + a[i].first - a[pre[i]].first);
        }
    }
    printf("%lld\n", f[n][delta]);
    return 0;
}

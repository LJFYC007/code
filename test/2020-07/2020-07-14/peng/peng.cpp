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
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, m, t, ans, f[maxn], sum[maxn], pre[maxn], suf[maxn];
pii a[maxn], p[maxn];

signed main()
{
    freopen("peng.in", "r", stdin);
    freopen("peng.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i].first); 
    REP(i, 1, m) { scanf("%lld", &a[i + n].first); a[i + n].second = 1; }
    n += m; sort(a + 1, a + n + 1);
    REP(i, 1, n) 
    {
        p[++ t] = pii(i, i);
        while ( p[t].y < n && a[i].y == a[p[t].y + 1].y ) ++ p[t].y;
        i = p[t].y;
    }
    REP(i, 1, n) f[i] = INF; f[0] = 0;
    REP(i, 2, t)
    {
        sum[p[i].x] = 0;
        REP(j, p[i].x + 1, p[i].y) sum[j] = sum[j - 1] + a[j].x - a[p[i].x].x;
        sum[p[i - 1].y] = 0;
        for ( int j = p[i - 1].y - 1; j >= p[i - 1].x; -- j ) sum[j] = sum[j + 1] + a[p[i - 1].y].x - a[j].x;
        int val = a[p[i].x].x - a[p[i - 1].y].x;
        if ( p[i - 1].x == p[i - 1].y ) 
        {
            REP(j, p[i].x, p[i].y) 
                f[j] = min(f[j], min(f[p[i - 1].x - 1], f[p[i - 1].x]) + sum[j] + (j - p[i].x + 1) * val);
            continue ;
        }
        int x = p[i].x;
        REP(j, p[i - 1].x - 1, p[i - 1].y + 1) suf[j] = pre[j] = INF;

        for ( int j = p[i - 1].y; j >= p[i - 1].x; -- j ) 
            suf[j] = min(suf[j + 1], f[j - 1] + sum[j]);

        REP(j, p[i - 1].x, p[i - 1].y)
            pre[j] = min(pre[j - 1], f[j - 1] + sum[j] + (p[i - 1].y - j + 1) * val);

        REP(j, p[i].x, p[i].y) 
        {
            int l = max(p[i - 1].x, 2 * x - j - 1);
            if ( l <= p[i - 1].y ) f[j] = min(f[j], suf[l] + sum[j] + (j - x + 1) * val);

            int r = min(p[i - 1].y, 2 * x - j - 2);
            if ( r >= p[i - 1].x ) f[j] = min(f[j], pre[r] + sum[j]);
        }
    }
    // REP(i, 1, n) printf("%lld ", f[i]); puts("");
    printf("%lld\n", f[n]);
    return 0;
}

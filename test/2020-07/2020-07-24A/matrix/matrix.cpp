/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 14时30分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
#define y1 nmsl

const int maxn = 2010;

int n, m, p, q, a[maxn][maxn];

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &p, &q);
    REP(i, 1, p)
    {
        int x1, y1, x2, y2; scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        ++ a[x1][y1]; ++ a[x2 + 1][y2 + 1];
        -- a[x1][y2 + 1]; -- a[x2 + 1][y1];
    }
    REP(i, 1, n) REP(j, 1, m) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    REP(i, 1, n) REP(j, 1, m) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    REP(i, 1, q)
    {
        int x1, y1, x2, y2; scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        int ans = a[x2][y2] + a[x1 - 1][y1 - 1] - a[x2][y1 - 1] - a[x1 - 1][y2];
        printf("%lld\n", ans);
    }
    return 0;
}

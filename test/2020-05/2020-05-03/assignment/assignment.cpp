/***************************************************************
	File name: assignment.cpp
	Author: ljfcnyali
	Create time: 2020年05月03日 星期日 08时47分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 250 + 10;

int T, n, m;
long double f[maxn][maxn], g[maxn][maxn], fac[maxn], ans1, ans2;

signed main()
{
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        ans1 = 0; ans2 = 0;
        mem(f); mem(g);
        REP(i, 1, n)
        {
            if ( i > m ) { fac[i] = 0; break ; }
            fac[i] = 1;
            REP(j, m - i + 1, m) fac[i] *= j;
            REP(j, 1, i) fac[i] /= j;
        }
        REP(K, 1, n)
        {
            f[0][0] = 1;
            REP(i, 1, n) REP(j, 1, i) f[i][j] = f[i - 1][j] + f[i - 1][j - 1] - (i - 1 - K >= 0 ? f[i - 1 - K][j - 1] : 0);
            REP(i, 1, n)
            {
                ans1 += (f[n][i] - g[n][i]) * fac[i] * K;
                g[n][i] = f[n][i]; 
            }
        }
        REP(i, 1, n) ans2 += g[n][i] * fac[i];
        printf("%.6Lf\n", ans1 / ans2);
    }
    return 0;
}

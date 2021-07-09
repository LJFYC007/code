/***************************************************************
	File name: difference.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 09时38分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int INF = 1e18;

int n, a[maxn], g[maxn][maxn], ans[maxn][maxn][2], Stack[maxn][2], tot, sum[maxn];
long double f[maxn][maxn];

signed main()
{
    freopen("difference.in", "r", stdin);
    freopen("difference.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); sum[i] = sum[i - 1] + a[i] * a[i]; a[i] += a[i - 1]; }
    REP(i, 0, n) REP(j, 0, n) f[i][j] = INF; 
    f[0][0] = 0;
    REP(i, 1, n)
        REP(j, i, n)
            REP(k, 0, i - 1)
            {
                int x = a[j] - a[i - 1], y = a[i - 1] - (k > 0 ? a[k - 1] : 0);
                int lenx = j - i + 1, leny = i - k, ret = sum[j] - sum[i - 1]; 
                long double tmp = x * x * 1.0 / lenx;
                if ( x * leny >= y * lenx && f[i][j] > f[k][i - 1] + ret - tmp ) 
                {
                    f[i][j] = f[k][i - 1] + ret - tmp;
                    ans[i][j][0] = x; ans[i][j][1] = lenx;
                    g[i][j] = k;
                }
            }
    int x = 0; long double Max = INF;
    REP(i, 1, n) if ( f[i][n] < Max ) { Max = f[i][n]; x = i; }
    REP(i, x, n)
    {
        Stack[++ tot][0] = ans[x][n][0]; 
        Stack[tot][1] = ans[x][n][1];     
    }
    while ( x ) 
    {
        int y = g[x][n]; -- x;
        if ( !y || !x ) continue ;
        REP(i, y, x)
        {
            Stack[++ tot][0] = ans[y][x][0]; 
            Stack[tot][1] = ans[y][x][1];
        }
        x = y;
    }
    for ( int i = tot; i >= 1; -- i ) 
    {
        int x = __gcd(Stack[i][0], Stack[i][1]);
        printf("%lld/%lld ", Stack[i][0] / x, Stack[i][1] / x);
    }
    puts("");
    return 0;
}

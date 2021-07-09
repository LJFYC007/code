/***************************************************************
	File name: CF102482D.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 19时18分31秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 1010;
 
int n, m, k;
long double f[maxn][maxn], c[maxn][maxn], ans, fac[maxn], g[maxn][maxn];
 
inline long double calc1(int n, int m, int x)
{
    if ( m < n * x ) return 0;
    if ( n == 0 || m < n * x + 1 ) return m == 0;
    return c[m - n * x - 1][n - 1] / fac[n];
}

inline long double calc2(int n, int m)
{
    if ( n < 0 || m < 0 ) return 0;
    return f[n][m] / fac[n];
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; REP(i, 0, n) c[i][0] = 1;
    REP(i, 1, n) REP(j, 1, i) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i;
    scanf("%d%d%d", &n, &m, &k);
    REP(x, 0, m) 
    {
        REP(i, 0, n) REP(j, 0, m) f[i][j] = g[i][j] = 0; f[0][0] = 1;
        REP(i, 1, n) REP(j, 0, m) REP(k, 0, x - 1) if ( j >= k ) f[i][j] += f[i - 1][j - k];

        REP(len, 1, n) REP(j, 0, m - len * x) 
            REP(i, max(0, k - len), k - 1) 
                g[n - len][m - len * x] += (j + k * x + x) * calc1(i, j, x) * calc2(n - len - i, m - len * x - j);

        continue ;

        REP(len, 1, n) if ( m - len * x >= 0 ) 
            ans += fac[n] / fac[len] * g[n - len][m - len * x];
        REP(i, 0, m) 
        {
            REP(l, 1, k) REP(r, k, n) 
            {
                int len = r - l + 1;
                long double ret = fac[n] / fac[len];
                ret *= -l * x;
                ret *= calc1(l - 1, i, x) * calc2(n - r, m - i - len * x);
                ans += ret;
            }
        }
    }
    ans = ans / c[n + m - 1][n - 1];
    printf("%.6Lf\n", ans + k);
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 110;

int dp[maxn][maxn][5], a[maxn][maxn], n, m, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n)
        REP(j, 1, m) 
            scanf("%d", &a[i][j]);
    if ( m == 1 ) 
    {
        REP(i, 1, n)
            REP(j, 1, k)
            {
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0]) + a[i][1];
                dp[i][j][0] = max(dp[i - 1][j][1], dp[i - 1][j][0]);
            }
        printf("%d\n", max(dp[n][k][0], dp[n][k][1]));
    }  
    else 
    {
        REP(i, 1, n)
            REP(j, 1, k)
            {
                // 0
                dp[i][j][0] = max(dp[i - 1][j][0], max(dp[i - 1][j][1], max(dp[i - 1][j][2], 
                                max(dp[i - 1][j][3], dp[i - 1][j][4]))));
                // 1
                dp[i][j][1] = max(dp[i - 1][j - 1][0], max(dp[i - 1][j - 1][2], dp[i - 1][j - 1][4]));
                dp[i][j][1] = max(dp[i][j][1], max(dp[i - 1][j][1], dp[i - 1][j][3])) + a[i][1];

                // 2
                dp[i][j][2] = max(dp[i - 1][j - 1][0], max(dp[i - 1][j - 1][1], dp[i - 1][j - 1][4]));
                dp[i][j][2] = max(dp[i][j][2], max(dp[i - 1][j][2], dp[i - 1][j][3])) + a[i][2];
                
                // 3
                dp[i][j][3] = max(dp[i - 1][j - 1][1], max(dp[i - 1][j - 1][2], dp[i - 1][j][3])) + a[i][1] + a[i][2];
                if ( j >= 2 ) 
                    // dp[i][j][3] = max(dp[i][j][3], dp[i - 1][j - 2][4] + a[i][1] + a[i][2]);
                    dp[i][j][3] = max(dp[i][j][3], max(dp[i - 1][j - 2][0], dp[i - 1][j - 2][4]) + a[i][1] + a[i][2]);

                // 4
                dp[i][j][4] = max(dp[i - 1][j - 1][0], max(dp[i - 1][j - 1][1], max(dp[i - 1][j - 1][2], 
                            max(dp[i - 1][j - 1][3], dp[i - 1][j][4])))) + a[i][1] + a[i][2];
            }
        int ans = 0;
        REP(i, 1, n) REP(j, 1, k) REP(p, 0, 4) ans = max(ans, dp[i][j][p]);
        printf("%d\n", ans);
    }
    return 0;
}

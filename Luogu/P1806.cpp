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

const int maxn = 510;

LL dp[maxn][maxn], n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) dp[i][i] = 1;
    REP(i, 1, n)
    {
        REP(j, 1, i - 1)
        {
            REP(k, 1, j - 1)
            {
                if ( i >= j + k ) 
                    dp[i][j] += dp[i - j][k];
            } 
        }    
    }
    LL ans = 0;
    // REP(i, 1, n) { REP(j, 1, i) printf("%d ", dp[i][j]); puts(""); }
    REP(i, 1, n - 1) ans += dp[n][i];
    printf("%lld\n", ans);
    return 0;
}

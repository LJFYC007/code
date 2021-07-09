#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 4010;

int dp[maxn][maxn], n, m, val[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    REP(i, 1, n)
    {
        char c[3];
        int x, y; scanf("%s%d%d", c, &x, &y);
        val[c[0] - 'a' + 1] = min(x, y);
    }
    for ( int i = m; i >= 1; -- i ) s[i] = s[i - 1];
    s[0] = 0;
    mem(dp);
    REP(i, 1, m) dp[i][i] = 0;
    REP(i, 1, m - 1) if ( s[i] == s[i + 1] ) dp[i][i + 1] = 0;
    REP(l, 0, m)
        REP(i, 1, m)
        {
            int j = i + l;
            if ( s[i - 1] == s[j + 1] ) dp[i - 1][j + 1] = min(dp[i][j], dp[i - 1][j + 1]);
            dp[i - 1][j] = min(dp[i - 1][j], dp[i][j] + val[s[i - 1] - 'a' + 1]);
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + val[s[j + 1] - 'a' + 1]);
        }
    printf("%d\n", dp[1][m]);
    return 0;
}

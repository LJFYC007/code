/***************************************************************
	File name: cactus.cpp
	Author: ljfcnyali
	Create time: 2019年09月13日 星期五 10时02分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long 
typedef long long LL;

const int maxn = 10010;
const int INF = 10000000000000;

int n, w, k, a[maxn], b[maxn], dp[maxn][5010], f[maxn], ans = INF;
int L, R, Mid;

inline void ReBuild()
{
    for ( int i = R; i >= L; -- i )
    {
        REP(j, 0, w) if ( i != R ) dp[i][j] = dp[i + 1][j]; else dp[i][j] = INF;
        dp[i][0] = 0;
        for ( int j = w; j >= a[i]; -- j ) dp[i][j] = min(dp[i][j], dp[i][j - a[i]] + b[i]);
    }
    REP(i, 0, w) f[i] = INF; f[0] = 0;
}

inline void Add(int x)
{
    for ( int j = w; j >= a[x]; -- j ) f[j] = min(f[j], f[j - a[x]] + b[x]);
}

inline bool pd()
{
    int sum = INF;
    REP(i, 0, w)
    {
        int x = dp[L][i];
        if ( R > Mid ) x += f[w - i];
        else x += i == w ? 0 : INF;
        sum = min(sum, x);
    }
    if ( sum <= k ) return true;
    return false;
}

signed main()
{
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &w, &k);
    REP(i, 1, n) scanf("%lld%lld", &a[i], &b[i]);
    REP(i, 1, n)
    {
        L = i; R = max(L, R);
        if ( L > Mid ) { ReBuild(); Mid = R; }
        // REP(j, 0, w) printf("%lld ", dp[i][j]); puts("");
        while ( R < n && !pd() ) Add(++ R);
        // REP(j, 0, w) printf("%lld ", f[j]); puts("");
        // printf("%lld %lld %lld\n", L, Mid, R);
        // puts("--------");
        if ( R == n && !pd() ) break ; 
        ans = min(ans, R - L + 1);
    }
    if ( ans != INF ) printf("%lld\n", ans);
    else puts("-1");
    return 0;
}

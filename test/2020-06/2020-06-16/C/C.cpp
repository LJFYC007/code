/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月16日 星期二 09时51分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int INF = 1e18;

int n, a[maxn], d[maxn], f1[maxn][maxn], f2[maxn][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1) scanf("%lld", &d[i]); 
    REP(i, 1, n) scanf("%lld", &a[i]); 
    REP(i, 1, n) REP(j, 0, n) f1[i][j] = f2[i][j] = INF;
    f1[1][0] = a[1]; f1[1][1] = a[1] + a[1]; f2[1][1] = 0;
    REP(i, 1, n - 1) REP(j, 0, i)
    {
        f1[i + 1][j + 1] = min(f1[i + 1][j + 1], f1[i][j] + a[i + 1] + a[i + 1] + d[i] * j);
        f1[i + 1][j] = min(f1[i + 1][j], f1[i][j] + a[i + 1] + d[i] * j);
        if ( j >= 1 ) f1[i + 1][j - 1] = min(f1[i + 1][j - 1], f1[i][j] + d[i] * j);
        else f2[i + 1][1] = min(f2[i + 1][1], f1[i][0] + d[i] * j);

        if ( j == 0 ) continue ;
        f2[i + 1][j + 1] = min(f2[i + 1][j + 1], f2[i][j] + d[i] * j);
        f2[i + 1][j] = min(f2[i + 1][j], f2[i][j] + a[i + 1] + d[i] * j);
        if ( j > 1 ) f2[i + 1][j - 1] = min(f2[i + 1][j - 1], f2[i][j] + a[i + 1] + a[i + 1] + d[i] * j);
        else if ( j == 1 ) f1[i + 1][0] = min(f1[i + 1][0], f2[i][j] + a[i + 1] + a[i + 1] + d[i] * j);
    }
    printf("%lld\n", f1[n][0]);
    return 0;
}

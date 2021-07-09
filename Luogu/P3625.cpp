/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2019年09月29日 星期日 15时08分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1510;

int T, n, m, len[3], A[maxn][maxn], ans, sum[maxn][maxn];
int s[maxn][maxn], a[maxn][maxn], b[maxn][maxn], c[maxn][maxn], d[maxn][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    scanf("%lld", &len[0]);
    REP(i, 1, n) REP(j, 1, m) { scanf("%lld", &A[i][j]); sum[i][j] = A[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]; }
    REP(i, len[0], n) REP(j, len[0], m) 
        s[i][j] = sum[i][j] - sum[i - len[0]][j] - sum[i][j - len[0]] + sum[i - len[0]][j - len[0]];
    REP(i, len[0], n) REP(j, len[0], m) a[i][j] = max(s[i][j], max(a[i - 1][j], a[i][j - 1]));
    REP(i, len[0], n) for ( int j = m - len[0] + 1; j >= 1; -- j ) 
        b[i][j] = max(s[i][j + len[0] - 1], max(b[i - 1][j], b[i][j + 1]));
    for ( int i = n - len[0] + 1; i >= 1; -- i ) REP(j, len[0], m) 
        c[i][j] = max(s[i + len[0] - 1][j], max(c[i + 1][j], c[i][j - 1]));
    for ( int i = n - len[0] + 1; i >= 1; -- i ) for ( int j = m - len[0] + 1; j >= 1; -- j )
        d[i][j] = max(s[i + len[0] - 1][j + len[0] - 1], max(d[i + 1][j], d[i][j + 1]));
    REP(i, len[0], n - 1) REP(j, len[0], m - len[0]) 
    {
        if ( i + len[0] > n || j + len[0] > n ) continue ; 
        ans = max(ans, a[i][m] + c[i + 1][j] + d[i + 1][j + 1]);
    }
    REP(i, 1, n - len[0] + 1) REP(j, len[0], m - len[0])
    {
        if ( i <= len[0] || i <= len[0] ) continue ;
        ans = max(ans, d[i][1] + a[i - 1][j] + b[i - 1][j + 1]);
    }
    REP(i, len[0], n - len[0]) REP(j, len[0], m - 1)
    {
        if ( j + len[0] > m || j + len[0] > m ) continue ;
        ans = max(ans, a[n][j] + b[i][j + 1] + d[i + 1][j + 1]);
    }
    REP(i, len[0], n - len[0]) REP(j, max(len[0], len[0]), m - len[0])
        ans = max(ans, a[i][j] + c[i + 1][j] + b[n][j + 1]);
    REP(i, len[0], n) REP(j, len[0] + len[0], m - len[0])
        ans = max(ans, a[n][j - len[0]] + b[n][j + 1] + s[i][j]);
    REP(i, len[0] + len[0], n - len[0]) REP(j, len[0], n)
        ans = max(ans, a[i - len[0]][m] + b[j + 1][m] + s[i][j]);
    printf("%lld\n", ans);
    return 0;
}

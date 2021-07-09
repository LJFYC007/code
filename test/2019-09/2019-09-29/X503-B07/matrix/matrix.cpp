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

const int maxn = 1010;

int T, n, m, len[3], A[maxn][maxn], ans, sum[maxn][maxn];
int s[maxn][maxn][3], a[maxn][maxn][3], b[maxn][maxn][3], c[maxn][maxn][3], d[maxn][maxn][3];
int dt[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        ans = -0x3f3f3f3f3f3f;
        scanf("%lld%lld", &n, &m);
        REP(i, 0, 2) scanf("%lld", &len[i]);
        REP(i, 1, n) REP(j, 1, m) { scanf("%lld", &A[i][j]); sum[i][j] = A[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]; }
        memset(s, -0x3f, sizeof(s));
        REP(k, 0, 2) REP(i, len[k], n) REP(j, len[k], m) 
            s[i][j][k] = sum[i][j] - sum[i - len[k]][j] - sum[i][j - len[k]] + sum[i - len[k]][j - len[k]];
        memset(a, -0x3f, sizeof(a));
        memset(b, -0x3f, sizeof(b));
        memset(c, -0x3f, sizeof(c));
        memset(d, -0x3f, sizeof(d));
        REP(k, 0, 2)
        {
            REP(i, len[k], n) REP(j, len[k], m) a[i][j][k] = max(s[i][j][k], max(a[i - 1][j][k], a[i][j - 1][k]));
            REP(i, len[k], n) for ( int j = m - len[k] + 1; j >= 1; -- j ) 
                b[i][j][k] = max(s[i][j + len[k] - 1][k], max(b[i - 1][j][k], b[i][j + 1][k]));
            for ( int i = n - len[k] + 1; i >= 1; -- i ) REP(j, len[k], m) 
                c[i][j][k] = max(s[i + len[k] - 1][j][k], max(c[i + 1][j][k], c[i][j - 1][k]));
            for ( int i = n - len[k] + 1; i >= 1; -- i ) for ( int j = m - len[k] + 1; j >= 1; -- j )
                d[i][j][k] = max(s[i + len[k] - 1][j + len[k] - 1][k], max(d[i + 1][j][k], d[i][j + 1][k]));
        }
        REP(k, 0, 5)
        {
            int x = dt[k][0], y = dt[k][1], z = dt[k][2]; 
            REP(i, len[x], n - 1) REP(j, len[y], m - len[z]) 
            {
                if ( i + len[y] > n || j + len[z] > n ) break ; 
                ans = max(ans, a[i][m][x] + c[i + 1][j][y] + d[i + 1][j + 1][z]);
            }
            REP(i, 1, n - len[x] + 1) REP(j, len[y], m - len[z])
            {
                if ( i <= len[y] || i <= len[z] ) break ;
                ans = max(ans, d[i][1][x] + a[i - 1][j][y] + b[i - 1][j + 1][z]);
            }
            REP(i, len[y], n - len[z]) REP(j, len[x], m - 1)
            {
                if ( j + len[y] > m || j + len[z] > m ) break ;
                ans = max(ans, a[n][j][x] + b[i][j + 1][y] + d[i + 1][j + 1][z]);
            }
            REP(i, len[y], n - len[z]) REP(j, max(len[y], len[z]), m - len[x])
                ans = max(ans, a[i][j][y] + c[i + 1][j][z] + b[n][j + 1][x]);
            REP(i, len[y], n) REP(j, len[x] + len[y], m - len[z])
                ans = max(ans, a[n][j - len[y]][x] + b[n][j + 1][z] + s[i][j][y]);
            REP(i, len[x] + len[y], n - len[z]) REP(j, len[y], n)
                ans = max(ans, a[i - len[y]][m][x] + b[j + 1][m][z] + s[i][j][y]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

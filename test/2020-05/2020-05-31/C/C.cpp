/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月01日 星期一 08时47分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;
const int Mod = 1e9 + 7;

int n, m, pre[maxn][maxn], suf[maxn][maxn], dp[maxn], ans, f[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Solve(int n, int m)
{
    mem(pre); mem(suf); mem(dp); mem(f);
    REP(i, 0, n) pre[0][i] = 1;
    REP(i, 1, m) 
    {
        REP(j, 0, n) pre[i][j] = (pre[i][j] + pre[i - 1][j]) % Mod;
        REP(j, 1, n) pre[i][j] = (pre[i][j] + pre[i][j - 1]) % Mod;
    }
    REP(i, 0, n) suf[m + 1][i] = 1;
    for ( int i = m; i >= 1; -- i ) 
    {
        REP(j, 0, n) suf[i][j] = (suf[i][j] + suf[i + 1][j]) % Mod;
        REP(j, 1, n) suf[i][j] = (suf[i][j] + suf[i][j - 1]) % Mod;
    }
    REP(i, 1, n) REP(j, 1, m) dp[i] = (dp[i] + (pre[j][i] - pre[j][i - 1]) * suf[j + 1][i - 1]) % Mod;
    dp[0] = 1;
    REP(i, 0, n) REP(j, 0, n) if ( i + j < n ) ans = (ans + (dp[i] * dp[j] % Mod) * power(m + 1, n - i - j)) % Mod;
    
    REP(i, 2, m) REP(j, 1, n) f[i][j] = (f[i][j - 1] + suf[i][n - j - 1] * (suf[i][j] - suf[i][j - 1])) % Mod;

    int sum = 0;
    REP(i, 1, m - 1) REP(j, 1, n - 1)
    {
        int L = n - j + 1, R = n - 1;
        if ( L > R ) continue ;
        int ret = (f[i + 1][R] - f[i + 1][L - 1]) % Mod;
        sum = (sum + (pre[i][n - j - 1] * (pre[i][j] - pre[i][j - 1]) % Mod) * ret) % Mod;
    }
    ans = (ans + sum * 2) % Mod;

    sum = 0;
    REP(i, 1, m - 1) REP(j, 0, n) 
    {
        int k = n - j;
        int ret = pre[i][n - j - 1] * suf[i + 1][n - k - 1] % Mod;
        sum = (sum + (ret * (pre[i][j] - pre[i][j - 1]) % Mod) * (suf[i + 1][k] - suf[i + 1][k - 1])) % Mod;
    }
    ans = (ans + sum) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    Solve(n, m); Solve(m, n);
    printf("%lld\n", (ans + Mod) % Mod); 
    return 0;
}

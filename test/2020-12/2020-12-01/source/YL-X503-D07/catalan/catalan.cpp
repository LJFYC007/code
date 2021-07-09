/***************************************************************
	File name: catalan.cpp
	Author: ljfcnyali
	Create time: 2020年12月01日 星期二 08时02分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int Mod = 998244353;

int n, m, dp[maxn][maxn], F[maxn][maxn], G[maxn][maxn];
bool vis[maxn][maxn];

inline bool Check(int l, int r, int L, int R)
{
    if ( l == r ) return F[l][R] - F[l][L - 1] == 0;
    REP(i, l, r) REP(j, L, R)
        if ( vis[i][j] ) return false;
    return true;
}

signed main()
{
    freopen("catalan.in", "r", stdin);
    freopen("catalan.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); ++ F[u][v]; ++ G[u][v]; }
    REP(i, 1, n) REP(j, 1, n) F[i][j] += F[i][j - 1];
    REP(j, 1, n) REP(i, 1, n) G[i][j] += G[i - 1][j];
    REP(i, 1, n + 1) dp[i][i] = dp[i][i - 1] = 1;

    REP(len, 2, n) REP(i, 1, n - len + 1)
    {
        int j = i + len - 1; 
        int sum = 0;
        REP(k, i, j) 
        {
            if ( k > i ) sum += G[j][k - 1] - G[k][k - 1];
            if ( sum == 0 && Check(k, k, k + 1, j) && Check(k, k, i, k - 1) )
                dp[i][j] = (dp[i][j] + dp[i][k - 1] * dp[k + 1][j]) % Mod;
            sum -= F[k + 1][k - 1] - F[k + 1][i - 1];
        }
    }
    printf("%lld\n", (dp[1][n] + Mod) % Mod);
    return 0;
}

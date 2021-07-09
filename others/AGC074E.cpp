/***************************************************************
	File name: AtCoder074E.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 08时41分45秒
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
const int Mod = 1e9 + 7;

int f[maxn][maxn][maxn], n, m, ans;
bool vis[maxn][maxn][maxn];

inline void Solve(int l, int r, int x)
{
    if ( x == 1 ) 
    {
        REP(i, l, r - 1) REP(j, 0, r - 1) vis[r][i][j] = vis[r][j][i] = true;
        return ;
    }
    if ( x == 2 )
    {
        REP(i, l, r - 1) REP(j, l, r - 1) vis[r][i][j] = true;
        REP(i, 0, l - 1) REP(j, 0, l - 1) vis[r][i][j] = true;
        return ;
    }
    REP(i, 0, l - 1) REP(j, 0, r) vis[r][j][i] = vis[r][i][j] = true;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m)
    {
        int l, r, x; scanf("%lld%lld%lld", &l, &r, &x);
        Solve(l, r, x);
    }
    f[1][0][0] = 1;
    REP(i, 1, n - 1)
    {
        REP(j, 0, i - 1)
            REP(k, 0, max(0ll, j - 1))
            {
                if ( vis[i][j][k] || !f[i][j][k] ) continue ;
                f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % Mod;
                f[i + 1][i][k] = (f[i + 1][i][k] + f[i][j][k]) % Mod;
                f[i + 1][i][j] = (f[i + 1][i][j] + f[i][j][k]) % Mod;
            }
    }
    REP(i, 0, n - 1) REP(j, 0, max(0ll, i - 1)) if ( !vis[n][i][j] ) ans = (ans + f[n][i][j]) % Mod;
    printf("%lld\n", (ans * 3) % Mod);
    return 0;
}

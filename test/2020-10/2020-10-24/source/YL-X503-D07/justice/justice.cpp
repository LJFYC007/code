/***************************************************************
	File name: justice.cpp
	Author: ljfcnyali
	Create time: 2020年10月24日 星期六 16时51分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6010;
const int Mod = 1e9 + 7;

int n, m, k, x, y, f[maxn][maxn][2], ans;

signed main()
{
    freopen("justice.in", "r", stdin);
    freopen("justice.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld", &m, &n, &k, &x, &y);
    if ( x == y ) { puts("1"); return 0; }
    f[0][0][1] = 1;
    REP(i, 1, n + m)
    {
        int sum = 0;
        REP(j, 0, m)
        {
            f[i][j][1] = (f[i][j][1] + sum) % Mod;
            f[i][j][0] = (f[i][j][0] + f[i - 1][j][0]) % Mod;
            f[i][j][0] = (f[i][j][0] + f[i - 1][j][1]) % Mod;
            sum = (sum + f[i - 1][j][1] + f[i - 1][j][0]) % Mod;
            if ( j >= k - 1 ) sum = (sum - f[i - 1][j - k + 1][1] - f[i - 1][j - k + 1][0]) % Mod;

            if ( j % (k - 1) == m % (k - 1) )
            {
                int x = i * (k - 1) - j + 1;
                if ( x < 0 || x % (k - 1) != n % (k - 1) || x > n ) continue ;
                ans = (ans + f[i][j][1]) % Mod;
            }
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

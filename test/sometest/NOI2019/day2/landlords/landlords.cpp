/***************************************************************
	File name: landlords.cpp
	Author: ljfcnyali
	Create time: 2019年07月18日 星期四 08时59分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;
const int Mod = 998244353;

int n, m, type, q;
LL ans[maxn], dp[maxn][maxn][2], a[maxn];

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod; b >>= 1;
    }
    return r;
}

inline int gcd(int a, int b) { if ( !b ) return a; return gcd(b, a % b); }

inline int frac(int a, int b) 
{
    if ( a == 0 || b == 0 ) return 0;
    int x = gcd(a, b); a /= x; b /= x;
    return (a * power(b, Mod - 2)) % Mod;
}

int main()
{
    freopen("landlords.in", "r", stdin);
    freopen("landlords.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &type);    
    REP(i, 1, n) a[i] = type == 1 ? i : i * i;
    REP(o, 1, m)
    {
        int x; scanf("%d", &x);
        dp[x + 1][n - x][0] = dp[x][n - x + 1][1] = 1;
        for ( int i = x; i >= 0; -- i )
            for ( int j = n - x; j >= 0; -- j )
            {
                dp[i][j][0] = frac(i, i + j);
                if ( dp[i + 1][j][0] != 1 || dp[i][j + 1][1] != 1 )
                    dp[i][j][0] = (dp[i][j][0] * (dp[i + 1][j][0] + dp[i][j + 1][1])) % Mod;
                dp[i][j][1] = frac(j, i + j);
                if ( dp[i + 1][j][0] != 1 || dp[i][j + 1][1] != 1 )
                    dp[i][j][1] = (dp[i][j][1] * (dp[i + 1][j][0] + dp[i][j + 1][1])) % Mod;
            }
        mem(ans);
        REP(i, 0, x) REP(j, 0, n - x) 
        {
            ans[i + j] += (a[i] * dp[i][j][0]) % Mod + (a[x + j] * dp[i][j][1]) % Mod;
            ans[i + j] %= Mod;
        }
        REP(i, 1, n) a[i] = ans[i];
    }
    scanf("%d", &q);
    REP(i, 1, q) { int x; scanf("%d", &x); printf("%lld\n", a[x]); }
    return 0;
}

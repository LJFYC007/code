/***************************************************************
	File name: permutation.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 08时45分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;
const int N = 3000;
const int Mod = 1e9 + 7;

int T, n, k, f[maxn][maxn], ans;

inline int power(int a, int b) 
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    REP(i, 1, N) f[i][0] = power(2, i - 1);
    REP(i, 1, N)
        REP(j, 1, (i + 1) / 2)
        {
            f[i][j] = (2 * j + 2) * f[i - 1][j] % Mod;
            if ( i - 2 * j >= 0 ) f[i][j] = (f[i][j] + (i - 2 * j) * f[i - 1][j - 1]) % Mod;
        }
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &k);
        int ret = 0;
        REP(i, 0, n - k - 1) ret = (ret + f[n][i]) % Mod;
        printf("%lld\n", ret);
    }
    return 0;
}

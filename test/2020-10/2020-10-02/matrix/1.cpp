/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时00分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3010;
const int Mod = 998244353;

int n, m, l[maxn], r[maxn], f[maxn][maxn];

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]);
    sort(l + 1, l + n + 1); sort(r + 1, r + n + 1);
    f[0][0] = 1;
    REP(i, 1, m)
    {
        int num = 0;
        REP(j, 1, n) if ( r[j] <= i ) ++ num;
        REP(j, 0, num) f[i][j] = f[i - 1][j];
        for ( int j = num; j >= 1; -- j ) f[i][j] = (f[i][j] + f[i][j - 1] * (num - j + 1)) % Mod;
        REP(j, 0, num) REP(k, 1, n) if ( l[k] == i ) f[i][j] = f[i][j] * (l[k] - k - j + 1) % Mod;

        // REP(j, 0, n) printf("%lld ", f[i][j]); puts("");
    }
    printf("%lld\n", (f[m][n] + Mod) % Mod);
    return 0;
}

/***************************************************************
	File name: E1.cpp
	Author: ljfcnyali
	Create time: 2020年04月16日 星期四 14时54分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], f[1010][1010];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n)
    {
        int x; scanf("%lld", &x);
        REP(j, 0, m - 1) a[j] += (x >> j) & 1;
    }
    f[0][0] = 1;
    REP(i, 1, n) REP(j, 0, 63)
    {
        f[i][j] = (f[i][j] + f[i - 1][j]) % Mod;
        f[i][j] = (f[i][j] + f[i - 1][j ^ a[i]]) % Mod;
    }
    REP(i, 0, m) printf("%lld ", f[n][i]); puts("");
    return 0;
}

/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年10月31日 星期六 20时16分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, k, f[3010][3010];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    f[0][0] = 1;
    REP(i, 1, n) for ( int j = i; j >= 1; -- j )
        f[i][j] = (f[i - 1][j - 1] + f[i][j * 2]) % Mod;
    printf("%lld\n", f[n][k]);
    return 0;
}

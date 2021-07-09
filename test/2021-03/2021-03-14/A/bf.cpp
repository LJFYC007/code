/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 08时58分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, k, a[maxn], f[maxn][110];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 0, n) REP(j, 0, k) f[i][j] = INF; f[0][0] = 0;
	REP(i, 1, n) REP(j, 1, k) REP(o, 0, i - 1)
		f[i][j] = min(f[i][j], f[o][j - 1] + (a[i] - a[o + 1]) * (a[i] - a[o + 1]));
	printf("%lld\n", f[n][k]);
    return 0;
}

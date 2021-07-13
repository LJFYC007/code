/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 09时45分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int INF = 1e18;

int n, q, a[maxn], f[maxn][maxn][2], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("ansput.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n + 1) REP(j, 0, n) REP(o, 0, 1) f[i][j][o] = -INF;
	f[n + 1][0][0] = 0;
	for ( int i = n; i >= 1; -- i ) REP(j, 0, n)
	{
		f[i][j][0] = max(f[i + 1][j][0], f[i + 1][j][1]);
		if ( j >= 1 ) f[i][j][1] = f[i + 1][j - 1][0] + a[i];
	}
	while ( q -- ) 
	{
		int i, c; scanf("%lld%lld", &i, &c);	
		ans = max(f[i][c][0], f[i][c][1]);	
		printf("%lld\n", ans);
	}
    return 0;
}

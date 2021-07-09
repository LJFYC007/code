/***************************************************************
	File name: ranklist.cpp
	Author: ljfcnyali
	Create time: 2021年04月16日 星期五 20时08分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, m, a[13]; LL f[1 << 13][13][510], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); int Max = 0, pos = 0;
	REP(i, 0, n - 1) { scanf("%d", &a[i]); if ( a[i] > Max ) { Max = a[i]; pos = i; } }
	f[0][pos][m] = 1;
	REP(i, 0, (1 << n) - 1) REP(j, 0, n - 1) REP(k, 0, m) if ( f[i][j][k] ) 
	{
		int num = n; REP(o, 0, n - 1) if ( (i >> o) & 1 ) -- num;	
		REP(o, 0, n - 1) if ( !((i >> o) & 1) )
		{
			int val = max(a[j] - a[o] + (o > j), 0);
			if ( num * val <= k ) f[i | (1 << o)][o][k - val * num] += f[i][j][k];
		}
	}
	REP(j, 0, n - 1) REP(k, 0, m) ans += f[(1 << n) - 1][j][k];
	printf("%lld\n", ans);
    return 0;
}

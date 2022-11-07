/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, sum[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	sum[1] = 1; REP(i, 2, 2000) sum[i] = sum[i - 1] + i;
	while ( T -- )
	{
		scanf("%d", &n);
		int ans = 10000000;
		REP(i, 1, 2000) if ( sum[i] >= n ) ans = min(ans, i + sum[i] - n);
		REP(i, 1, 2000) if ( 2 <= sum[i] - n && sum[i] - n <= i + 1 ) ans = min(ans, i);
		printf("%d\n", ans);
	}
    return 0;
}

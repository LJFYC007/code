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
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, T, a[maxn], c[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld", &n, &m);
		REP(i, 1, n) scanf("%lld", &a[i]); sort(a + 1, a + n + 1);
		REP(i, 1, m) scanf("%lld", &c[i]);
		int now = 0, Min = n + 1, ans = 0;
		for ( int i = n; i >= 1; -- i )
		{
			Min = min(Min, a[i] - i + n);
			if ( now + 1 > Min || c[now + 1] > c[a[i]] )
			{
				REP(j, 1, i) ans += c[a[j]];
				break ;
			}
			++ now; ans += c[now];
		}
		printf("%lld\n", ans);
	}
    return 0;
}

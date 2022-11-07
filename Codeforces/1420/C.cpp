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
const int INF = 1e18;

int T, n, q, a[maxn];

inline int Get(int x)
{
	if ( x < 1 || x > n ) return 0;
	if ( a[x] > a[x - 1] && a[x] > a[x + 1] ) return a[x];
	if ( a[x] < a[x - 1] && a[x] < a[x + 1] ) return -a[x];
	return 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld", &n, &q);
		REP(i, 1, n) scanf("%lld", &a[i]);
		a[0] = a[n + 1] = -1;
		int ans = 0;
		REP(i, 1, n)
		{
			if ( a[i] > a[i - 1] && a[i] > a[i + 1] ) ans += a[i];
			if ( a[i] < a[i - 1] && a[i] < a[i + 1] ) ans -= a[i];
		}
		printf("%lld\n", ans);
		while ( q -- )
		{
			int x, y; scanf("%lld%lld", &x, &y);
			REP(i, x - 1, x + 1) ans -= Get(i);
			REP(i, max(x + 2, y - 1), y + 1) ans -= Get(i);
			swap(a[x], a[y]);
			REP(i, x - 1, x + 1) ans += Get(i);
			REP(i, max(x + 2, y - 1), y + 1) ans += Get(i);
			printf("%lld\n", ans);
		}
	}
    return 0;
}

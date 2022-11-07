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

const int maxn = 1e5 + 10;

int T, n, a[maxn], num[50];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld", &n);
		REP(i, 1, n)
		{
			int x; scanf("%lld", &x);
			REP(j, 0, 31) if ( (x >> j) & 1 ) a[i] = j;
		}
		mem(num);
		int ans = 0;
		for ( int i = n; i >= 1; -- i )
		{
			ans += num[a[i]];
			++ num[a[i]];
		}
		cout << ans << endl;
	}
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long
#define pii pair<int, int>
typedef long long LL;

int T, n, p[40], a[40];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%I64d", &T);
	p[0] = 1; REP(i, 1, 38) p[i] = p[i - 1] * 3;
	while ( T -- )
	{
		scanf("%I64d", &n);
		for ( int i = 38; i >= 0; -- i )
			if ( n >= p[i] )
			{
				n -= p[i]; a[i] = 1;
			}
			else a[i] = 0;
		int now = 0;
		if ( n >= 1 )
		{
			while ( a[now] == 1 ) ++ now;
			a[now] = 1;
		}
		int ans = 0;
		REP(i, now, 38) ans += a[i] * p[i];
		printf("%I64d\n", ans);
	}
	return 0;
}

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

const int maxn = 2e5 + 10;

int T, W, n;
pii a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T --  )
	{
		scanf("%lld%lld", &n, &W);
		REP(i, 1, n) { scanf("%lld", &a[i].first); a[i].second = i; }
		sort(a + 1, a + n + 1);
		int sum = 0;
		REP(i, 1, n) if ( a[i].first * 2 >= W && a[i].first <= W )
		{
			printf("1\n%lld\n", a[i].second);
			goto Next ;
		}
		REP(i, 1, n)
		{
			sum += a[i].first;
			if ( sum > W ) break ;
			if ( sum * 2 >= W )
			{
				printf("%lld\n", i);
				REP(j, 1, i) printf("%lld ", a[j].second); puts("");
				goto Next ;
			}
		}
		puts("-1");
		Next : ;
	}
    return 0;
}

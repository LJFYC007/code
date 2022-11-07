/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int T, n, q, ans1, ans2, a[maxn];
map<int, int> Map;
vector<int> d[maxn];

inline int calc(int x)
{
	int tmp = x;
	for ( int i = 0; i < d[tmp].size(); ++ i )
	{
		int y = d[tmp][i];
		while ( x % (y * y) == 0 ) x /= (y * y);
	}
	return x;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	REP(i, 2, maxn - 10) for ( int j = i; j <= maxn - 10; j += i ) if ( j % (i * i) == 0 ) d[j].push_back(i);
	while ( T -- )
	{
		scanf("%lld", &n); Map.clear();
		REP(i, 1, n) { int x; scanf("%lld", &x); a[i] = calc(x); ++ Map[a[i]]; }

		ans1 = ans2 = 0;
		REP(i, 1, n) ans1 = max(ans1, Map[a[i]]);
		REP(i, 1, n) if ( a[i] > 1 && Map[a[i]] % 2 == 0 )
		{
			Map[1] += Map[a[i]]; Map[a[i]] = 0;
		}
		REP(i, 1, n) ans2 = max(ans2, Map[a[i]]);
		ans2 = max(ans2, Map[1]);

		scanf("%lld", &q);
		REP(i, 1, q)
		{
			int x; scanf("%lld", &x);
			if ( x == 0 ) printf("%lld\n", ans1);
			else printf("%lld\n", ans2);
		}
	}
    return 0;
}

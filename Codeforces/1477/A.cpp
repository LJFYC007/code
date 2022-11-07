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

int T, n, k, a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld", &n, &k);
		REP(i, 1, n) scanf("%lld", &a[i]);
		int g = 0;
		REP(i, 2, n) g = __gcd(g, abs(a[i] - a[i - 1]));
		bool flag = false;
		REP(i, 1, n) if ( abs(k - a[i]) % g == 0 ) flag = true;
		if ( flag ) puts("YES");
		else puts("NO");
	}
    return 0;
}

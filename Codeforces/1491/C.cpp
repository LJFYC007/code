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
const int INF = 1e9;

int T, n, a[maxn], b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		int ans = 0;
		scanf("%lld", &n); 
		REP(i, 1, n) { scanf("%lld", &a[i]); b[i] = 0; }
		REP(i, 1, n)
		{
			ans += max(a[i] - 1 - b[i], 0ll);
			b[i] -= a[i] - 1;
			REP(j, 2, min(n - i, a[i])) ++ b[i + j];
			if ( b[i] > 0 ) b[i + 1] += b[i];
		}
		printf("%lld\n", ans);
	}
    return 0;
}

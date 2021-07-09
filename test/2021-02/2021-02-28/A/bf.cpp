#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e5 + 10;

int n, a[maxn], b[maxn], m, t[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1,n) scanf("%lld%lld", &a[i], &b[i]);
	REP(i, 1, m) scanf("%lld", &t[i]);
	REP(i, 1, n)
	{
		int x = 1, val = a[i];
		REP(j, 1, m)
			if ( t[j] >= val ) { x = 3 - x; val = x == 1 ? a[i] : b[i]; } 
		ans += val;
	}
	printf("%lld\n", ans);
	return 0;
}

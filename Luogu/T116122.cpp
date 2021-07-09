#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], m, ans[maxn], ret;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); a[i] += a[i - 1]; }
	scanf("%d", &m);
	REP(i, 1, n)
	{
		int L = a[i];
		int pos = lower_bound(a + 1, a + n + 1, L + L) - a;
		//printf("%d %d\n", i, pos);
		if ( pos > n ) { ++ ans[L]; break ; }
		int R = a[pos] - a[i] - 1;
		++ ans[L]; -- ans[R + 1];
	}
	REP(i, 1, m) ans[i] += ans[i - 1];
	REP(i, 1, m) if ( ans[i] ) ++ ret;
	printf("%d\n", ret);
	REP(i, 1, m) if ( ans[i] ) printf("%d ", i); puts("");
	return 0;
}

#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, x, d[maxn], a[maxn], pre[maxn], suf[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &x);
	REP(i, 1, n) { scanf("%lld", &d[i]); a[i] = d[i] * (d[i] + 1) / 2; }
    // REP(i, 1, n) printf("%lld ", a[i]); puts("");
	REP(i, 1, n) { a[i] += a[i - 1]; pre[i] = pre[i - 1] + d[i]; }
    // REP(i, 1, n) printf("%lld ", a[i]); puts("");
	int L = 1;
	REP(i, 1, n)
	{
		if ( L >= i )
		{
			while ( pre[n] - pre[L] + pre[i] > x && L <= n ) ++ L;
			if ( L > n ) L = 1;
		}
		if ( L < i ) while ( pre[i] - pre[L] > x ) ++ L;
		int sum = (L > i || (L == i && d[L] < x)) ? a[n] - a[L] + a[i] : a[i] - a[L];
		int num = (L > i || (L == i && d[L] < x)) ? pre[n] - pre[L] + pre[i] : pre[i] - pre[L];
		num = x - num;
		int r = d[L], l = r - num + 1;
        if ( num > d[L] ) continue ;
		ans = max(ans, sum + (l + r) * num / 2);
        // cerr << L << " " << i << " " << l << " " << r << " " << num << endl;
	}
	printf("%lld\n", ans);
	return 0;
}

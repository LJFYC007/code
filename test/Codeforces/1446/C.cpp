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

int n, a[maxn], ans;

inline int Solve(int Max, int l, int r)
{
	if ( l + 1 >= r ) return r - l + 1;
	int val[33]; REP(i, 0, Max) val[i] = 0;
	REP(i, l, r)
	{
		bool flag = false;
		for ( int j = Max; j >= 1; -- j )
			if ( (a[i] >> j - 1) & 1 ) { flag = true; ++ val[j]; break ; }
		if ( !flag ) ++ val[0];
	}

	int ans = 2, lst = l + val[0];
	bool flag = val[0] ? true : false;
	REP(i, 1, Max)
	{
		if ( !val[i] ) continue ;
		int ret = Solve(i - 1, lst, lst + val[i] - 1); lst += val[i];
		if ( flag ) ++ ret;
		REP(j, i + 1, Max) if ( val[j] ) ++ ret;
		ans = max(ans, ret); flag = true;
	}
    // REP(i, l, r) cout << a[i] << " "; cout << endl;
    // cout << Max << " " << l << " " << r << " " << ans << endl;
	return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	ans = max(2ll, Solve(32, 1, n));
	printf("%lld\n", n - ans);
    return 0;
}

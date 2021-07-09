#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Max = 2e16;

int x[maxn], y[maxn], ax, ay, bx, by, xs, xy, t, ans, N, sum[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &x[0], &y[0], &ax, &ay, &bx, &by);
	scanf("%I64d%I64d%I64d", &xs, &xy, &t);
	REP(i, 1, 100)
	{
		x[i] = x[i - 1] * ax + bx;
		y[i] = y[i - 1] * ay + by;
        // printf("%I64d %I64d\n", x[i], y[i]);
		if ( x[i] <= 0 || y[i] <= 0 || x[i] >= Max || y[i] >= Max ) { N = i - 1; break ; }
		sum[i] = sum[i - 1] + x[i] + y[i] - x[i - 1] - y[i - 1];
        // printf("%I64d %I64d %I64d\n", sum[i], sum[i - 1], sum[i] - sum[i - 1]);
		// if ( sum[i] - sum[i - 1] > t ) { N = i; break ; }
	}
	REP(i, 0, N)
	{
		int ret = abs(x[i] - xs) + abs(y[i] - xy);
        // printf("%I64d %I64d\n", i, ret);
		if ( ret > t || ret < 0 ) continue ;
		for ( int j = i; j >= 0; -- j ) if ( ret + sum[i] - sum[j] <= t ) ans = max(ans, i - j + 1); else break ;
		REP(j, i + 1, N) if ( ret + sum[j] - sum[i] <= t ) ans = max(ans, j - i + 1); else break ;
	}
	printf("%I64d\n", ans);
	return 0;
}

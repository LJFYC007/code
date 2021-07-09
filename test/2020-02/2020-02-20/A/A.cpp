#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], ans, sum[2][maxn];
char s[maxn];

signed main()
{
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%lld", &n); scanf("%s", s + 1);
	/*
	REP(i, 1, n)
	{
		a[i] = a[i - 1] + s[i] - '0';
		if ( a[i] & 1 ) ++ sum1[a[i]]; else ++ sum2[a[i]];
	}
	REP(i, 1, 2 * n) { sum1[i] += sum1[i - 1]; sum2[i] += sum2[i - 1]; }
	*/
//	sum[b] - sum[a - 1] = sum[c] - (sum[b] - 1)
//	2sum[b] = sum[a - 1] + sum[c] + 1
	//int L = 1, R = a[n] * 2 - 1;
	int x = 0, l1 = 0, l2 = 0; sum[0][0] = 1;
	REP(i, 1, n)
	{
		REP(j, 0, 1) sum[j][i] = sum[j][i - 1];
		if ( s[i] == '1' )
		{
			ans += sum[x][l2 - 1]; x ^= 1;
			l2 = l1; l1 = i;
		}
		else if ( l1 > 1 ) ans += sum[x ^ 1][l1 - 2];
		++ sum[x][i];
		/*
		continue ;
		int x = a[i], l = L - x, r = R - x;
		if ( r <= x ) break ;
		l = max(l, x + 1);
		if ( r & 1 ) ans += sum1[r] - sum1[max(l - 1, 0)];
		else ans += sum2[r] - sum2[max(l - 1, 0)];
		printf("%lld %lld %lld\n", x, l, r);
		if ( r & 1 ) printf("%lld %lld\n", sum1[r], sum1[max(l - 1, 0)]);
		else printf("%lld %lld\n", sum2[r], sum2[max(l - 1, 0)]);
		printf("%lld\n", ans);*/
	}
	printf("%lld\n", ans);
	return 0;
}

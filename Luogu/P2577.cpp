#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
const int maxn = 210;

struct node
{
	int a, b;
} s[maxn];
int dp[maxn][maxn * maxn], n, sum[maxn];

inline int cmp(node a, node b)
{
	return a.b > b.b;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &s[i].a, &s[i].b);
	sort ( s + 1, s + n + 1, cmp );
	REP(i, 1, n) sum[i] = sum[i - 1] + s[i].a;
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	REP(i, 1, n)
		REP(j, 0, sum[i])
		{
			if ( j >= s[i].a ) 
				dp[i][j] = min(dp[i][j], max(dp[i - 1][j - s[i].a], j + s[i].b));
			dp[i][j] = min(dp[i][j], max(dp[i - 1][j], sum[i] - j + s[i].b));
		}
	int ans = 0x3f3f3f3f;
	REP(i, 0, sum[n])
		ans = min(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}


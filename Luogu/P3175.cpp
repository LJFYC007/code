#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, s[maxn];
double ans, f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 0, (1 << n) - 1)
	{
		scanf("%lf", &f[i]);
		s[i] = s[i >> 1] + (i & 1);
	}
	REP(i, 0, n - 1) REP(j, 0, (1 << n) - 1) if ( (j >> i) & 1 ) f[j] += f[j - (1 << i)];
	REP(i, 1, (1 << n) - 1)
	{
		double val = 1 - f[((1 << n) - 1) ^ i];
		if ( val == 0 ) { puts("INF"); return 0; }
		ans += ((s[i] & 1) ? 1 : -1) / val;
	}
	printf("%.7lf\n", ans);
	return 0;
}

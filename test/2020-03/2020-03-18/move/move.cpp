#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, ans, a[maxn];

signed main()
{
	freopen("move.in", "r", stdin);
	freopen("move.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) { int x; scanf("%lld", &x); ++ a[x]; }
	a[1] = 1 - a[1];
	REP(i, 2, n) a[i] = a[i - 1] + 1 - a[i];
	sort(a + 1, a + n + 1);
	REP(i, 1, n) ans += abs(a[n / 2 + 1] - a[i]);
	printf("%lld\n", ans);
	return 0;
}

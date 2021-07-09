#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, a[maxn], f[maxn], g[maxn];

inline int get(int l, int r)
{
	int sum = g[r] - g[l + 1];
	return sum + 2 * a[l] * a[l + 1];
}

signed main()
{
	freopen("ring.in", "r", stdin);
	freopen("ring.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) { scanf("%lld", &a[i]); f[0] += a[i] * a[i]; }
	sort(a + 1, a + n + 1);
	REP(i, 3, n) g[i] = g[i - 1] + a[i] * (a[i - 1] + a[i - 2]) - a[i - 1] * a[i - 2];
	REP(i, 1, n / 2)
	{
		if ( n % i != 0 ) continue ;
		int x = i, l = 1, r = n / x;
		REP(j, 1, x)
		{
			f[i] += get(l, r);
			l += n / x; r += n / x;
		}
	}
	REP(i, 1, m)
	{
		int k; scanf("%lld", &k);
		if ( k == 0 ) { printf("%lld\n", f[k]); continue ; }
		printf("%lld\n", f[__gcd(k, n)]);
	}
	return 0;
}

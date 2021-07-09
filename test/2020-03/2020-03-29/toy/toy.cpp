#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 10010;

int n, m, len1, len2, b[maxn], a[maxn], c[maxn];

inline int Check(int x)
{
	int ret = 0;
	REP(i, 1, len2) ret += lower_bound(a + 1, a + len1 + 1, x - b[i]) - a - 1;
	return ret;
}

inline void Solve()
{
	int len3 = 0;
	int L = 0, R = 1e9, w = 0;
	while ( L <= R )
	{
		int Mid = L + R >> 1, x = Check(Mid);
		if ( x == m ) { w = Mid; break ; }
		if ( x < m ) { L = Mid + 1; w = Mid; }
		else R = Mid - 1;
	}
	++ w;
	REP(i, 1, len2) REP(j, 1, lower_bound(a + 1, a + len1 + 1, w - b[i]) - a - 1) c[++ len3] = b[i] + a[j];
	sort(c + 1, c + len3 + 1);
	len3 = min(len3, m);
	REP(i, 1, len3) a[i] = c[i];
	len1 = len3;
}

signed main()
{
	freopen("toy.in", "r", stdin);
	freopen("toy.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	scanf("%lld", &len1);
	REP(i, 1, len1) scanf("%lld", &a[i]);
	sort(a + 1, a + len1 + 1);
	REP(i, 2, n)
	{
		scanf("%lld", &len2);
		REP(j, 1, len2) scanf("%lld", &b[j]);
		sort(b + 1, b + len2 + 1);
		Solve();
	}
	REP(i, 1, m) printf("%lld\n", a[i]);
	return 0;
}

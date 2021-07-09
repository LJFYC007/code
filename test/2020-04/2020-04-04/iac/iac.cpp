#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int c[maxn], a[maxn], n, k, m, ans;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

signed main()
{
	freopen("iac.in", "r", stdin);
	freopen("iac.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &k, &m);
	REP(i, 1, n) { scanf("%lld", &a[i]); if ( a[i] == 2 ) add(i, 1); }
	REP(i, 1, m)
	{
		int op; scanf("%lld", &op);
		if ( op == 1 )
		{
			int x; scanf("%lld", &x);
			if ( a[x] == 2 ) add(x, -1);
			if ( a[x + 1] == 2 ) add(x + 1, -1);
			swap(a[x], a[x + 1]);
			if ( a[x] == 2 ) add(x, 1);
			if ( a[x + 1] == 2 ) add(x + 1, 1);
		}
		else
		{
			int l, r; scanf("%lld%lld", &l, &r);
			int sum = r - l + 1 - get(r) + get(l - 1);
			ans = (r - l + 1) * (n - 1);
			if ( get(n) ) ans += sum * k;
			printf("%lld\n", ans);
		}
	}
	return 0;
}

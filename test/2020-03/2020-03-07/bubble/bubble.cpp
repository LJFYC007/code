#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, p[maxn], c[3][maxn], f[maxn], ret;

inline int lowbit(int x) { return x & -x; }

inline void add(int op, int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[op][i] += val; }

inline int get(int op, int l, int r)
{
	int sum = 0;
	for ( int i = r; i > 0; i -= lowbit(i) ) sum += c[op][i];
	for ( int i = l - 1; i > 0; i -= lowbit(i) ) sum -= c[op][i];
	return sum;
}

signed main()
{
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n)
	{
		scanf("%lld", &p[i]);
		add(0, p[i], 1); f[i] = get(0, p[i], n);
		add(1, f[i], f[i]); add(2, f[i], 1);
	}
	REP(i, 1, m)
	{
		int t, x; scanf("%lld%lld", &t, &x);
		if ( t == 1 )
		{
			int u = p[x], v = p[x + 1]; swap(p[x], p[x + 1]);
			add(1, f[x], -f[x]); add(2, f[x], -1);
			add(1, f[x + 1], -f[x + 1]); add(2, f[x + 1], -1);
			swap(f[x], f[x + 1]);
			if ( u < v )
			{
				++ f[x + 1];
				add(1, f[x], f[x]); add(2, f[x], 1);
				add(1, f[x + 1], f[x + 1]); add(2, f[x + 1], 1);
			}
			else
			{
				-- f[x];
				add(1, f[x], f[x]); add(2, f[x], 1);
				add(1, f[x + 1], f[x + 1]); add(2, f[x + 1], 1);
			}
		}
		else
		{
			if ( x >= n ) { puts("0"); continue ; }
			++ x;
			int ans = get(1, x, n) - get(2, x, n) * x;
			printf("%lld\n", ans); ret ^= ans;
		}
	}
	return 0;
}

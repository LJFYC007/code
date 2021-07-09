#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, N, ans;
struct node { int l, r; } a[maxn], b[maxn * 2];

inline bool cmp(node a, node b) { return a.r - a.l < b.r - b.l; }

inline bool cmp2(node a, node b) { return a.r < b.r || (a.r == b.r && a.l < b.l); }

inline int Solve(int L, int R)
{
	sort(b + 1, b + N + 1, cmp2);
	int now = 1, ret = 0, last = L;
	while ( last <= R )
	{
		while ( b[now].l < last && now <= N ) ++ now;
		if ( now > N || b[now].r > R ) return ret;
		last = b[now].r; ++ ret;
	}
	return ret;
}

int main()
{
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d%d", &m, &n);
	REP(i, 1, n)
	{
		scanf("%d%d", &a[i].l, &a[i].r);
		if ( a[i].l > a[i].r ) a[i].r += m;
		else
		{
			a[i].r += m; a[i].l += m;
			b[++ N] = a[i];
			a[i].r -= m; a[i].l -= m;
		}
		b[++ N] = a[i];
	}
	sort(a + 1, a + n + 1, cmp);
	REP(i, 1, min(20, n)) ans = max(ans, Solve(a[i].r, a[i].l + m) + 1);
	printf("%d\n", ans);
	return 0;
}

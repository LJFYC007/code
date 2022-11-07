#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int n, a[maxn], ans[maxn], r[maxn], l;
set<int> Set;

inline int cmp(int x, int y) { return a[x] > a[y]; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		scanf("%d", &a[i]); Set.insert(i); r[i] = i;
	}
	sort(r + 1, r + n + 1, cmp); Set.insert(n + 1);
	if ( a[r[1]] <= a[r[n]] *2 ) { REP(i, 1, n) printf("-1 "); puts(""); return 0; }
	int x = 1;
	REP(i, 1, n)
	{
		while ( x <= n && a[r[i]] <= a[r[x]] * 2 ) Set.erase(r[x ++]);
		if ( x > n ) break ;
		ans[r[i]] = *Set.upper_bound(r[i]);
		if ( ans[r[i]] == n + 1 ) ans[r[i]] = *Set.begin() + n;
	}
	REP(i, 1, n) if ( ans[i] ) ans[i + n] = ans[i] + n;
	for ( int i = n + n; i >= 1; -- i )
	{
		if ( ans[i + 1] == 0 ) continue ;
		if ( !ans[i] || ans[i] > ans[i + 1] ) ans[i] = ans[i + 1];
	}
	REP(i, 1, n) printf("%d ", ans[i] - i); puts("");
	return 0;
}

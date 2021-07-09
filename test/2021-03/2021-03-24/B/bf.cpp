#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, m;
struct node { int x, y, w; } a[maxn], b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].w);
	REP(i, 1, n) scanf("%lld%lld%lld", &b[i].x, &b[i].y, &b[i].w);
	scanf("%lld", &m);
	REP(o, 1, m)
	{
		int l, r; scanf("%lld%lld", &l, &r); int ans = -1;
		REP(i, 1, n) REP(j, 1, n) if ( a[i].y < b[j].y )
		{
			if ( a[i].x < l && r < b[j].x ) ans = max(ans, a[i].w + b[j].w);
			if ( l < a[i].x && b[j].x < r ) ans = max(ans, a[i].w + b[j].w);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

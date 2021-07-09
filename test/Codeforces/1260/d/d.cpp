#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 2e5 + 10;
 
int m, n, k, t, a[maxn];
struct node
{
	int l, r, d;
	bool operator < (const node &a) const { return l < a.l; }
} p[maxn];
 
inline bool Check(int Mid)
{
	int ret = 0, R = 0, now = 1;
	REP(i, 0, n + 1)
	{
		int x = R;
		while ( p[now].l == i && now <= k )
		{
			if ( p[now].d > Mid ) x = max(x, p[now].r);
			++ now;
		}
		ret += (x - R) * 2;
		R = max(R, x); R = max(R, i);
	}
	return ret + n + 1 <= t;
}
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d%d", &m, &n, &k, &t);
	REP(i, 1, m) { int x; scanf("%d", &x); ++ a[x]; }
	for ( int i = maxn - 2; i >= 0; -- i ) a[i] += a[i + 1];
	REP(i, 1, k) scanf("%d%d%d", &p[i].l, &p[i].r, &p[i].d);
	sort(p + 1, p + k + 1);
	int L = 0, R = maxn - 9, ans = 0;
	while ( L <= R )
	{
		int Mid = L + R >> 1;
		if ( Check(Mid) ) { ans = a[Mid]; R = Mid - 1; }
		else L = Mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}

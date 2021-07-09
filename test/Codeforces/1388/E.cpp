#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 4e6 + 10;
const double eps = 1e-8;
const double INF = 1e18;
 
int n, m, k;
pair<double, double> p[2010], f[maxn];
double t[maxn], g[maxn];
struct node { int l, r, y; } a[2010];
double ans = INF;

inline double Solve(double k)
{
	REP(i, 1, n) p[i] = make_pair(a[i].l - k * a[i].y, a[i].r - k * a[i].y);
	sort(p + 1, p + n + 1);
	REP(i, 1, n - 1) if ( p[i].second - eps > p[i + 1].first ) return INF;
	return p[n].second - p[1].first;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].y);
	ans = Solve(0);
	REP(i, 1, n) REP(j, i + 1, n)
	{
	    if ( a[i].y == a[j].y ) continue ;
		t[++ m] = (a[i].r - a[j].l) * 1.0 / (a[i].y - a[j].y);
        t[++ m] = (a[j].r - a[i].l) * 1.0 / (a[j].y - a[i].y);
        f[++ k] = make_pair(min(t[m - 1], t[m]), max(t[m - 1], t[m]));
    }
    sort(t + 1, t + m + 1); sort(f + 1, f + k + 1);
    int now = 1, num = 0;
    REP(i, 1, m)
    {
        while ( now <= k && f[now].second < t[i] + eps ) ++ now;
        if ( now > k || f[now].first > t[i] - eps ) g[++ num] = t[i];
    }
    int l = 1, r = num;
    while ( l <= r ) 
    {
        int L = l + (r - l + 1) / 3, R = r - (r - l + 1) / 3;
        double x = Solve(g[L]), y = Solve(g[R]);
        ans = min(ans, min(x, y));
        if ( y < x + eps ) l = L + 1; else r = R - 1;
    }
    REP(i, l - 50, l + 50) if ( i >= 1 && i <= num ) ans = min(ans, Solve(g[i]));
	printf("%.7lf\n", ans);
	return 0;
}

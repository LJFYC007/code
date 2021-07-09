#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 60;
const int INF = 0x3f3f3f3f;

struct point
{
	int x, y, w;
	bool operator < (const point &a) const { return x < a.x || (x == a.x && y < a.y); }
} a[maxn], b[maxn], O;

int n, ans[maxn], f[maxn][maxn][maxn], val[maxn][maxn];
bool vis[maxn][maxn][maxn];

inline int cmp(point x, point y) { return x.y * y.x > x.x * y.y; }

inline int cross(point a, point b, point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

inline bool Check(point a, point b, point c)
{
	if ( (cross(O, a, c) > 0) != (cross(a, b, c) > 0) ) return false;
	if ( (cross(O, a, c) > 0) != (cross(b, O, c) > 0) ) return false;
	return true;
}

inline void Solve(int n, int w)
{
	REP(i, 1, n) REP(j, 1, n) REP(k, 1, n) f[i][j][k] = INF;
	if ( b[1].x == 0 ) sort(b + 2, b + n + 1, cmp);
	else sort(b + 1, b + n + 1, cmp);
	REP(i, 1, n) REP(j, 1, n)
	{
		val[i][j] = b[j].w;
		REP(k, i + 1, j - 1)
			if ( Check(b[i], b[j], b[k]) ) { val[i][j] += b[k].w; vis[i][k][j] = false; }
			else vis[i][k][j] = true;
	}
	REP(i, 1, n) REP(j, i + 1, n)
	{
		f[i][j][2] = min(f[i][j][2], b[i].w + val[i][j]);
		REP(k, j + 1, n) if ( vis[i][j][k] ) REP(o, 2, n) f[j][k][o + 1] = min(f[j][k][o + 1], f[i][j][o] + val[j][k]);
	}
	REP(i, 1, n) REP(j, i + 1, n) REP(k, 2, j) ans[k + 1] = min(ans[k + 1], f[i][j][k] + w);
}

signed main()
{
	freopen("but.in", "r", stdin);
	freopen("but.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].w);
	sort(a + 1, a + n + 1);
	REP(i, 3, n) ans[i] = INF;
	REP(i, 1, n - 2)
	{
		REP(j, i + 1, n) { b[j - i] = a[j]; b[j - i].x -= a[i].x; b[j - i].y -= a[i].y; }
		Solve(n - i, a[i].w);
	}
	REP(i, 3, n) printf("%lld ", ans[i] >= INF ? -1 : ans[i]); puts("");
	return 0;
}

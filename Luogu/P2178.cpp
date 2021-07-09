#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int INF = 1e18;

int n, m, a[maxn], Min[maxn][19], Max[maxn][19], Log[maxn], st[maxn][19], ans1[maxn], ans2[maxn];
int x[maxn], y[maxn], c[maxn], sa[maxn], rk[maxn], height[maxn][19], tot;
char s[maxn];

inline bool cmp(int a, int b, int k) { return y[a] == y[b] && y[a + k] == y[b + k]; }

inline int Get1(int l, int r)
{
	int x = Log[r - l + 1];
	if ( height[l][x] < height[r - (1 << x) + 1][x] ) return st[l][x];
	return st[r - (1 << x) + 1][x];
}

inline int Get2(int l, int r)
{
	int x = Log[r - l + 1];
	return max(Max[l][x], Max[r - (1 << x) + 1][x]);
}

inline int Get3(int l, int r)
{
	int x = Log[r - l + 1];
	return min(Min[l][x], Min[r - (1 << x) + 1][x]);
}

inline void Solve(int l, int r)
{
	if ( l >= r ) return ;
	int pos = Get1(l + 1, r), val = height[pos][0];
	Solve(l, pos - 1); Solve(pos, r);
	ans1[val] += (pos - l) * (r - pos + 1);
	if ( Get2(l, pos - 1) != -INF && Get2(pos, r) != -INF ) ans2[val] = max(ans2[val], Get2(l, pos - 1) * Get2(pos, r));
	if ( Get3(l, pos - 1) != INF && Get3(pos, r) != INF ) ans2[val] = max(ans2[val], Get3(l, pos - 1) * Get3(pos, r));
	if ( val == 900 ) cerr << ans2[val] << endl;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", s + 1);
	REP(i, 1, n) scanf("%lld", &a[i]);

	REP(i, 0, maxn / 2)
	{
		ans2[i] = -INF;
		REP(j, 0, 18) { Min[i][j] = INF; Max[i][j] = -INF; }
	}

	m = 122;
	REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; }
	REP(i, 1, m) c[i] += c[i - 1];
	for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
	for ( int k = 1; k < n; k <<= 1 )
	{
		mem(c); tot = 0;
		REP(i, n - k + 1, n) y[++ tot] = i;
		REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
		REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
		for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
		REP(i, 1, n) y[i] = x[i]; x[sa[1]] = tot = 1;
		REP(i, 2, n) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? tot : ++ tot;
        if ( tot == n ) break ; m = tot;
	}
	REP(i, 1, n) rk[sa[i]] = i;
	for ( int i = 1, k = 0; i <= n; ++ i )
	{
		if ( k ) -- k;
		while ( s[i + k] == s[sa[rk[i] - 1] + k] ) ++ k;
		height[rk[i]][0] = k;
	}

	Log[2] = 1; REP(i, 3, n) Log[i] = Log[i >> 1] + 1;
	REP(i, 1, n) { st[i][0] = i; Max[i][0] = Min[i][0] = a[sa[i]]; }
	REP(j, 1, 18) REP(i, 1, n)
	{
		Min[i][j] = min(Min[i][j - 1], Min[i + (1 << j - 1)][j - 1]);
		Max[i][j] = max(Max[i][j - 1], Max[i + (1 << j - 1)][j - 1]);
		if ( height[i][j - 1] < height[i + (1 << j - 1)][j - 1] )
		{
			height[i][j] = height[i][j - 1];
			st[i][j] = st[i][j - 1];
		}
		else
		{
			height[i][j] = height[i + (1 << j - 1)][j - 1];
			st[i][j] = st[i + (1 << j - 1)][j - 1];
		}
	}

	Solve(1, n);
	for ( int i = n - 1; i >= 0; -- i ) { ans1[i] += ans1[i + 1]; ans2[i] = max(ans2[i], ans2[i + 1]); }
	REP(i, 0, n - 1) printf("%lld %lld\n", ans1[i], ans2[i] == -INF ? 0 : ans2[i]);
	return 0;
}

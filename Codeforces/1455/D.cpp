/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, ans, p[maxn];
pii a[maxn], t;

inline int dis(pii x, pii y) { return abs(x.x - y.x) + abs(x.y - y.y); }

inline int calc(int x)
{
	int ret = 0;
	ret += dis(a[p[2]], pii(a[p[1]].x + x * t.x, a[p[1]].y));
	ret += dis(a[p[3]], pii(a[p[1]].x, x * t.y + a[p[1]].y));
	ret += dis(a[p[4]], pii(a[p[1]].x + x * t.x, a[p[1]].y + x * t.y));
	return ret;
}

inline void Get()
{
	int L = 0, R = 1000000000;
	while ( L + 10 <= R )
	{
		int Midl = L + (R - L + 1) / 3, Midr = R - (R - L + 1) / 3;
		int vall = calc(Midl), valr = calc(Midr);
		ans = min(ans, min(vall, valr));
		if ( vall < valr ) R = Midr;
		else L = Midl;
	}
	REP(i, L, R) ans = min(ans, calc(i));
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%lld", &T);
	while ( T -- )
	{
		n = 4; REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
		ans = INF;
		REP(i, 1, 4) p[i] = i;
		do
		{
			t = pii(1, 1); Get();
			t = pii(1, -1); Get();
			t = pii(-1, 1); Get();
			t = pii(-1, -1); Get();
		} while ( next_permutation(p + 1, p + 4 + 1) );
		printf("%lld\n", ans);
	}
	return 0;
}

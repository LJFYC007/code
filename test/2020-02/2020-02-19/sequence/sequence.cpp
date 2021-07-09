#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 2147483647;

int n, a[maxn], ans, p[maxn], tot;
map<int, pii> Map1;
map<int, int> Map;
bool vis[maxn];
vector<pii> q;

signed main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	int Max = -INF, sum = 0;
	for ( int i = n; i >= 1; -- i )
	{
		sum = max(sum, Max - a[i]);
		Max = max(Max, a[i]);
	}
	Max = -INF;
	for ( int i = n; i >= 1; -- i )
	{
		if ( Max - a[i] == sum )
		{
			Map1[a[i]].first = i;
			if ( !Map1[a[i]].second ) Map1[a[i]].second = Map[a[i]] ? Map[a[i]] - 1 : n;
		}
		Max = max(Max, a[i]);
		Map[a[i]] = i;
	}
	REP(i, 1, n) if ( Map1[a[i]].first )
	{
		q.push_back(pii(Map1[a[i]].first, Map1[a[i]].second));
		Map1[a[i]].first = 0;
	}
	REP(o, 0, q.size() - 1)
	{
		int L = q[o].first, R = q[o].second;
		int x = a[L], y = a[L] + sum, sum1 = 0, sum2 = 0;
		tot = 0;
		REP(i, L, R)
		{
			if ( a[i] == x ) { ++ sum1; p[++ tot] = 0; }
			if ( a[i] == y ) { ++ sum2; p[++ tot] = 1; }
		}
		int ret = n + 1;
		REP(i, 0, sum1)
		{
			int num = sum1 - i, t = i;
			for ( int j = tot; j >= 1; -- j )
			{
				if ( !t ) break ;
				if ( p[j] == 0 ) -- t;
				else ++ num;
			}
			ret = min(ret, num);
		}
		ans += ret;
	}
	printf("%lld\n", ans);
	return 0;
}

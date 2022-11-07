/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, w[maxn], ans, deg[maxn];
vector<pii> p;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld", &n); int ans = 0; REP(i, 1, n) deg[i] = 0;
		REP(i, 1, n) { scanf("%lld", &w[i]); ans += w[i]; }
		REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); ++ deg[u]; ++ deg[v]; }
		p.clear();
		REP(i, 1, n) p.push_back(pii(w[i], i));
		printf("%lld ", ans);
		sort(p.begin(), p.end());
		reverse(p.begin(), p.end());
		REP(i, 0, p.size() - 1)
		{
			while ( deg[p[i].second] >= 2 )
			{
				-- deg[p[i].second]; ans += p[i].first;
				printf("%lld ", ans);
			}
		}
		puts("");
	}
    return 0;
}

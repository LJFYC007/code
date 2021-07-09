#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, p, q, Begin[maxn], Next[maxn], To[maxn], W[maxn], e;
vector<pii> Edge[maxn], a;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

pii operator + (pii a, int b) { return pii(a.first + b, a.second + b); }

signed main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%lld%lld%lld%lld", &n, &m, &q, &p);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); }
	Edge[1].push_back(pii(0, 0));
	double x = 1 - 1.0 / p;
	REP(u, 1, n)
	{
		sort(Edge[u].begin(), Edge[u].end());
		a.clear();
		for ( int j = 0; j < Edge[u].size(); ++ j )
		{
			while ( a.size() && Edge[u][j].first * x <= a.back().second )
			{
				Edge[u][j].first = a.back().first;
				Edge[u][j].second = max(Edge[u][j].second, a.back().second);
				a.pop_back();
			}
			a.push_back(Edge[u][j]);
		}
		swap(Edge[u], a);
		for ( int j = Begin[u]; j; j = Next[j] )
		{
			int v = To[j];
			for ( int k = 0; k < Edge[u].size(); ++ k ) Edge[v].push_back(Edge[u][k] + W[j]);
		}
	}
	REP(i, 1, q)
	{
		int t, d; scanf("%lld%lld", &t, &d);
		bool flag = false;
		for ( int j = 0; j < Edge[t].size(); ++ j )  if ( Edge[t][j].first * x <= d && d <= Edge[t][j].second ) { flag = true; break ; }
		printf("%lld", flag);
	}
	puts("");
	return 0;
}

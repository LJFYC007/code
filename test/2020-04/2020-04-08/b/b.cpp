#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4010;
const int INF = 1e18;

int n, m, k, s, t, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans, dis[maxn];
bool vis[maxn], flag;
struct node
{
	int u, v, w;
	bool operator < (const node &a) const { return w > a.w; }
} a[maxn];
priority_queue<pii> Q;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int SPFA()
{
	while ( !Q.empty() ) Q.pop();
	REP(i, 1, n) { dis[i] = INF; vis[i] = false; } dis[s] = 0; Q.push(pii(0, s));
	while ( !Q.empty() )
	{
		int u = Q.top().second; Q.pop();
		if ( vis[u] ) continue ; vis[u] = true;
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i];
			if ( dis[v] > dis[u] + W[i] )
			{
				dis[v] = dis[u] + W[i];
				Q.push(pii(-dis[v], v));
			}
		}
	}
	return dis[t];
}

signed main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%lld%lld%lld%lld%lld", &n, &m, &k, &s, &t);
	REP(i, 1, m) { scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w); add(a[i].u, a[i].v, a[i].w); }
	ans = INF; flag = true; ans = min(ans, SPFA()); flag = false;
	sort(a + 1, a + m + 1);
	REP(i, 1, m)
	{
		mem(Begin); e = 0;
		REP(j, 1, m) add(a[j].u, a[j].v, max(0ll, a[j].w - a[i].w));
		ans = min(ans, SPFA() + k * a[i].w);
	}
	printf("%lld\n", ans);
	return 0;
}

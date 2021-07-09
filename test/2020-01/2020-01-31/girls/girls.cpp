#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, A, B, C, ans, sum[maxn], a[maxn], tot, deg[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, vis[maxn];
vector<int> Edge[maxn];
pii q[maxn];

inline int choose(int n) { return n < 2 ? 0 : n * (n - 1) / 2; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int Solve(int x, int y, int z)
{
	if ( x > y ) swap(x, y);
	if ( x > z ) swap(x, z);
	if ( y > z ) swap(y, z);
	int ret = x * A + y * B + z * C;
	return ret;
}

signed main()
{
	freopen("girls.in", "r", stdin);
	freopen("girls.out", "w", stdout);
	scanf("%llu%llu", &n, &m);
	REP(i, 1, n - 1) sum[i] = sum[i - 1] + i;
	scanf("%llu%llu%llu", &A, &B, &C);
	REP(i, 1, m)
	{
		int x, y; scanf("%llu%llu", &x, &y); Edge[x].push_back(y); Edge[y].push_back(x);
		if ( x > y ) swap(x, y); ++ deg[x + 1]; ++ deg[y + 1]; q[i] = pii(x + 1, y + 1);
		if ( x > 0 ) ans -= sum[x - 1] * A + B * x * x + C * x * y;
		if ( x + 1 != y ) ans -= (sum[y - 1] - sum[x]) * B + A * (y - x - 1) * x + C * (y - x - 1) * y;
		if ( y < n - 1 ) ans -= A * (n - y - 1) * x + B * (n - y - 1) * y + (sum[n - 1] - sum[y]) * C;
	}
	REP(i, 1, m)
	{
		int u = q[i].first, v = q[i].second;
		if ( deg[u] < deg[v] || (deg[u] == deg[v] && u > v) ) swap(u, v);
		add(u, v);
	}
	REP(i, 1, n)
	{
		for ( int j = Begin[i]; j; j = Next[j] ) vis[To[j]] = i;
		for ( int j = Begin[i]; j; j = Next[j] )
		{
			int u = To[j];
			for ( int k = Begin[u]; k; k = Next[k] )
			{
				int v = To[k]; if ( vis[v] != i ) continue ;
				ans -= Solve(i - 1, u - 1, v - 1);
			}
		}
	}
	REP(i, 0, n - 1)
	{
		ans += A * choose(n - i - 1) * i;
		ans += B * (n - i - 1) * i * i;
		ans += C * choose(i) * i;
	}
	REP(i, 0, n - 1)
	{
		if ( !Edge[i].size() ) continue ;
		tot = 0;
		REP(j, 0, Edge[i].size() - 1) a[++ tot] = Edge[i][j];
		sort(a + 1, a + tot + 1);
		int num1 = 0, num2 = 0;
		REP(j, 1, tot) if ( a[j] < i ) ++ num1; else ++ num2;
		ans += i * C * choose(num1) + i * A * choose(num2) + i * num1 * num2 * B;
		int ret1 = 0;
		REP(j, 1, num1) { ans += A * ret1 + B * (j - 1) * a[j]; ret1 += a[j]; }
		int ret2 = 0;
		REP(j, num1 + 1, tot) { ans += B * ret2 + C * (j - num1 - 1) * a[j]; ret2 += a[j]; }
		ans += ret1 * num2 * A + ret2 * num1 * C;
	}
	printf("%llu\n", ans);
	return 0;
}

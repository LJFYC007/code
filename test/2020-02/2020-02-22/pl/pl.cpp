#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010 + 10;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], b[maxn], in[maxn], pre[maxn], id[maxn], vis[maxn];
bool use[maxn];
struct node { int u, v, w; node(int x = 0, int y = 0, int z = 0) { u = x; v = y; w = z; } } ;

inline int Solve(int root, int n, int m, node *Edge)
{
	int ret = 0;
	while ( 1 )
	{
		REP(i, 1, n) in[i] = INF;
		REP(i, 1, m) if ( Edge[i].u != Edge[i].v && Edge[i].w < in[Edge[i].v] ) { pre[Edge[i].v] = Edge[i].u; in[Edge[i].v] = Edge[i].w; }
		REP(i, 1, n) if ( i != root && in[i] == INF ) return -1;
		int num = 0; REP(i, 1, n) id[i] = vis[i] = -1;
		in[root] = 0;
		REP(i, 1, n)
		{
			ret += in[i]; int v = i;
			while ( vis[v] != i && id[v] == -1 && v != root ) { vis[v] = i; v = pre[v]; }
			if ( v != root && id[v] == -1 )
			{
				id[v] = ++ num;
				for ( int u = pre[v]; u != v; u = pre[u] ) id[u] = num;
			}
		}
		if ( num == 0 ) break ;
		REP(i, 1, n) if ( id[i] == -1 ) id[i] = ++ num;
		REP(i, 1, m)
		{
			int v = Edge[i].v; Edge[i].u = id[Edge[i].u]; Edge[i].v = id[Edge[i].v];
			if ( Edge[i].u != Edge[i].v ) Edge[i].w -= in[v];
		}
		n = num; root = id[root];
	}
	return ret;
}

node Edge[maxn];
int p[maxn], ID[maxn];

inline int Build()
{
	int N = 0, M = 0;
	REP(i, 1, n) if ( !use[i] ) { p[++ N] = i; ID[i] = N; }
	++ N;
	REP(i, 1, N - 1)
	{
		int val = a[p[i]] ^ b[p[i]];
		REP(j, 1, n) if ( use[j] ) val = min(val, b[j] ^ a[p[i]]);
		Edge[++ M] = node(N, i, val);
	}
	REP(i, 1, N - 1) REP(j, 1, N - 1) if ( i != j ) Edge[++ M] = node(i, j, b[p[i]] ^ a[p[j]]);
	return Solve(N, N, M, Edge);
}

signed main()
{
	freopen("pl.in", "r", stdin);
	freopen("pl.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n) scanf("%lld", &b[i]);
	REP(i, 1, n) Edge[++ m] = node(n + 1, i, a[i] ^ b[i]);
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) Edge[++ m] = node(i, j, b[i] ^ a[j]);
	int ans = Solve(n + 1, n + 1, m, Edge), sum = 0, pos = 0;
	printf("%lld\n", ans);
	REP(i, 1, n)
	{
		REP(j, 1, n)
		{
			if ( use[j] ) continue ;
			int val = INF; use[j] = true;
			REP(k, 1, n) if ( use[k] ) val = min(val, b[k] ^ a[j]);
			int x = Build(); use[j] = false;
			if ( x != -1 && x + sum + val == ans ) { sum += val; pos = j; break ; }
		}
		printf("%lld ", pos); use[pos] = true;
	}
	puts("");
	return 0;
}

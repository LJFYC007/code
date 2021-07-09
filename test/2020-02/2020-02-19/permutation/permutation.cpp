#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int a[maxn], b[maxn], n, m, c[maxn];
pii q[maxn];
vector<int> Edge[maxn];

namespace Subtask1
{
	inline int main()
	{
		int ans = 0;
		REP(i, 1, n) b[i] = i;
		do
		{
			REP(i, 1, m) if ( b[q[i].first] > b[q[i].second] ) goto Next;
			REP(i, 1, n) c[b[i]] = i;
			REP(i, 1, n)
			{
				int sum = 0;
				REP(j, i, n) { sum += a[c[j]]; ans = max(ans, sum); }
			}
			Next : ;
		} while ( next_permutation(b + 1, b + n + 1) );
		printf("%lld\n", ans);
		return 0;
	}
}

namespace Subtask2
{
	int ans, f[maxn][2];

	inline void DFS(int u)
	{
		f[u][1] = a[u];
		if ( Edge[u].size() ) REP(i, 0, Edge[u].size() - 1)
		{
			int v = Edge[u][i]; DFS(v);
			f[u][1] += f[v][1]; f[u][0] += f[v][0];
		}
		f[u][1] = max(f[u][1], 0ll);
		f[u][0] = max(f[u][0], f[u][1]);
		ans = max(ans, f[u][0]);
	}

	inline int main()
	{
		REP(i, 1, m) Edge[q[i].first].push_back(q[i].second);
		DFS(1); printf("%lld\n", ans);
		return 0;
	}
}

namespace Dinic
{
	const int INF = 1e18;
	int n, m, s, t, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], dis[maxn];

	inline void add(int u, int v, int w)
	{
	    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
	    To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0;
	}

	inline bool BFS(int s, int t)
	{
	    mem(dis); dis[s] = 1; queue<int> Q; Q.push(s);
	    while ( !Q.empty() )
	    {
	        int u = Q.front(); Q.pop();
	        for ( int i = Begin[u]; i; i = Next[i] )
	        {
	            int v = To[i]; if ( !W[i] || dis[v] ) continue ;
	            dis[v] = dis[u] + 1;
	            Q.push(v);
	        }
	    }
	    return dis[t];
	}

	inline int Dinic(int u, int t, int flow)
	{
	    if ( u == t || !flow ) return flow;
	    int f = 0;
	    for ( int i = Begin[u]; i; i = Next[i] )
	    {
	        int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ;
	        int x = Dinic(v, t, min(flow, W[i]));
	        if ( !x ) continue ;
	        f += x; flow -= x;
	        W[i] -= x; W[i ^ 1] += x;
    	}
    	if ( !f ) dis[u] = 0;
	    return f;
	}

	inline int Solve(int s, int t)
	{
    	int flow = 0;
 	   while ( BFS(s, t) ) while ( int x = Dinic(s, t, INF) ) flow += x;
 	   return flow;
	}
}

namespace Subtask3
{
	const int N = 2000;
	const int INF = 1e18;

	inline int main()
	{
		int S = n + n + 1, T = n + n + 2, ans = 2 * n * N;
		REP(i, 1, n)
		{
			ans += a[i];
			Dinic :: add(S, i, N + a[i]); Dinic :: add(i + n, T, N + a[i]);
			Dinic :: add(i, T, N); Dinic :: add(S, i + n, N);
			Dinic :: add(i + n, i, INF);
		}
		REP(i, 1, m)
		{
			Dinic :: add(q[i].first, q[i].second, INF);
			Dinic :: add(q[i].first + n, q[i].second + n, INF);
		}
		ans -= Dinic :: Solve(S, T);
		printf("%lld\n", ans);
		return 0;
	}
}

signed main()
{
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, m) scanf("%lld%lld", &q[i].first, &q[i].second);
	return Subtask3 :: main();
	if ( n <= 10 ) return Subtask1 :: main();
	else return Subtask2 :: main();
	return 0;
}

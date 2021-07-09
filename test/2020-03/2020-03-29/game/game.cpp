#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e16;

int Begin[maxn], From[maxn], Next[maxn], To[maxn], e, W[maxn], F[maxn];
int dis[maxn], a[maxn], s, t, pre[maxn];
bool vis[maxn];

inline void add(int u, int v, int f, int w)
{
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
	swap(u, v); f = 0; w = -w;
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
}

inline bool BFS(int s, int t)
{
    REP(i, 1, 300) dis[i] = INF; mem(vis);
    dis[s] = 0; vis[s] = true; a[s] = INF; queue<int> Q; Q.push(s);
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] && F[i] > 0 )
            {
                dis[v] = dis[u] + W[i];
                a[v] = min(a[u], F[i]);
                pre[v] = i;
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] != INF;
}

inline void SPFA(int s, int t, int &flow, int &cost)
{
    flow += a[t]; cost += a[t] * dis[t];
    int u = t;
    while ( u != s ) { F[pre[u]] -= a[t]; F[pre[u] ^ 1] += a[t]; u = From[pre[u]]; }
}

inline void MCMF(int s, int t, int &flow, int &cost)
{
    flow = cost = 0;
    while ( BFS(s, t) ) SPFA(s, t, flow, cost);
}

int n, m, k, C[maxn], ans1, ans2, Max[maxn], Val[maxn];
vector<int> Edge[maxn];

signed main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
	scanf("%lld%lld", &m, &k);
	REP(i, 1, m) { int x, y; scanf("%lld", &x); REP(j, 1, x) { scanf("%lld", &y); Edge[i].push_back(y); } }
	REP(i, 1, m) scanf("%lld%lld", &Max[i], &Val[i]);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &C[i]);
	ans1 = ans2 = INF;
	REP(i, 1, n)
	{
		if ( ans1 <= k * C[i] ) continue ;
		mem(Begin); e = 1;
		int S = 2 * m + 1, T = 2 * m, num = 0;
		REP(j, 1, n) if ( C[j] > C[i] )
		{
			++ num;
			add(S, j, 1, 0);
			for ( int k = 0; k < Edge[j].size(); ++ k ) add(j + m, Edge[j][k], INF, 0);
		}
		if ( num > Max[m] ) continue ;
		REP(j, 1, m - 1) add(j, j + m, Max[j], Val[j]);
		add(m, m + m, num, Val[m]);
		REP(j, n + 1, m) for ( int k = 0; k < Edge[j].size(); ++ k ) add(j + m, Edge[j][k], INF, 0);
    	int flow, cost;
    	MCMF(S, T, flow, cost);
		if ( flow >= num )
		{
			ans1 = k * C[i];
			ans2 = cost;
		}
	}
	printf("%lld %lld\n", ans1, ans2);
    return 0;
}

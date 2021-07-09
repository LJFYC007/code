#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int INF = 1e18;

int Begin[maxn], From[maxn], Next[maxn], To[maxn], e = 1, W[maxn], F[maxn];
int dis[maxn], a[maxn], s, t, pre[maxn], n, prime[maxn], tot, f[maxn], ans = 1;
bool vis[maxn];

inline void add(int u, int v, int f, int w)
{
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
	swap(u, v); f = 0; w = -w;
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
}

inline bool BFS(int s, int t)
{
	mem(vis); REP(i, 1, t) dis[i] = -INF;
	dis[s] = 0; vis[s] = true; a[s] = 1;
	queue<int> Q; Q.push(s);
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i];
            if ( dis[v] < dis[u] + W[i] && F[i] > 0 )
            {
                dis[v] = dis[u] + W[i];
                a[v] = min(a[u], F[i]);
                pre[v] = i;
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] > 0;
}

inline void SPFA(int s, int t)
{
    ans += a[t] * dis[t]; int u = t;
    while ( u != s ) { F[pre[u]] -= a[t]; F[pre[u] ^ 1] += a[t]; u = From[pre[u]]; }
}

signed main()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 2, n)
	{
		if ( !vis[i] ) prime[++ tot] = i;
		for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) break ;
		}
	}
	int s = tot + 1, t = tot + 2, sum = 0;
	REP(i, 1, tot)
		if ( prime[i] * prime[i] <= n ) { ++ sum; add(s, i, 1, 0); }
		else add(i, t, 1, 0);
	REP(i, 1, tot)
	{
		f[i] = prime[i];
		while ( f[i] * prime[i] <= n ) f[i] *= prime[i];
		ans += f[i];
	}
	REP(i, sum + 1, tot)
		REP(j, 1, sum)
		{
			int ret = prime[i];
			while ( ret * prime[j] <= n ) ret *= prime[j];
			if ( ret > f[i] + f[j] ) add(j, i, 1, ret - f[i] - f[j]);
		}
    while ( BFS(s, t) ) SPFA(s, t);
	printf("%lld\n", ans);
	return 0;
}

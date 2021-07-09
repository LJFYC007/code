/***************************************************************
	File name: AGC034D.cpp
	Author: ljfcnyali
	Create time: 2021年02月22日 星期一 10时41分14秒
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

int n, c[maxn], d[maxn], s, t, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], F[maxn];
int ans, dis[maxn], pre[maxn], Min[maxn], belong[maxn];
pii a[maxn], b[maxn];
bool vis[maxn];

inline void add(int u, int v, int w, int f)
{
	// cout << u << " " << v << " " << "(";
	// if ( w == INF ) cout << "INF";
	// else cout << w;
	// cout << "," << f << ")" << endl;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
	swap(u, v); w = 0; f = -f;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
}

inline bool SPFA()
{
	REP(i, 1, t) dis[i] = -INF; dis[s] = 0;
	queue<int> Q; Q.push(s); vis[s] = true; Min[s] = INF;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( !W[i] ) continue ;
			if ( dis[v] < dis[u] + F[i] )
			{
				dis[v] = dis[u] + F[i]; 
				Min[v] = min(Min[u], W[i]);
				pre[v] = u; belong[v] = i;
				if ( !vis[v] ) { vis[v] = true; Q.push(v); }
			}
		}
		vis[u] = false;
	}
	return dis[t] != -INF;
}

inline int DFS()
{
	int x = t, ret = Min[t] * dis[t];
	while ( x != s ) 
	{
		W[belong[x]] -= Min[t]; W[belong[x] ^ 1] += Min[t];
		x = pre[x];
	}
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &c[i]);
	REP(i, 1, n) scanf("%lld%lld%lld", &b[i].x, &b[i].y, &d[i]);

	s = n + n + 5; t = n + n + 6;
	REP(i, 1, n) 
	{
		add(s, i, c[i], 0); add(n + i, t, d[i], 0);
		add(i, n + n + 1, INF, a[i].x + a[i].y);
		add(i, n + n + 2, INF, a[i].x - a[i].y);
		add(i, n + n + 3, INF, -a[i].x + a[i].y);
		add(i, n + n + 4, INF, -a[i].x - a[i].y);
		add(n + n + 1, n + i, INF, -b[i].x - b[i].y);
		add(n + n + 2, n + i, INF, -b[i].x + b[i].y);
		add(n + n + 3, n + i, INF, b[i].x - b[i].y);
		add(n + n + 4, n + i, INF, b[i].x + b[i].y);
	}

	while ( SPFA() ) ans += DFS();
	printf("%lld\n", ans);
    return 0;
}

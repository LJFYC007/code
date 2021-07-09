/***************************************************************
	File name: kutulu.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 10时55分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, k, h, a[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int val, num, ans = INF, dis[maxn], sum, b[maxn], tut;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS(v, u);
	}
	sum += b[dis[u]] * a[u];
}

inline void DFS1(int u, int fa, int x, int dep)
{
	if ( dep % k == tut % k && dep >= tut && dep <= h ) sum += x * a[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u, x, dep + 1);
	}
}

inline void Solve(int u, int fa)
{
	if ( dis[u] <= h ) ans = min(ans, sum);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u, 1, 0); DFS1(u, v, -1, 0);
		Solve(v, u);
		DFS1(v, u, -1, 0); DFS1(u, v, 1, 0);
	}
}

signed main()
{
    freopen("kutulu.in", "r", stdin);
    freopen("kutulu.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &k, &h);
	REP(i, 1, n) { scanf("%lld", &a[i]); num += a[i]; } 
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	val = ((h - 1) / k + 1) * num;
	for ( int t = (h - 1) % k + 1; t <= min(n, h); t += k ) { ++ b[t]; val -= num; }
	for ( int t = n; t >= 0; -- t ) b[t] += b[t + 1];
	tut = (h - 1) % k + 1;

	sum = val; DFS(1, 0); Solve(1, 0);
	printf("%lld", ans);
    return 0;
}

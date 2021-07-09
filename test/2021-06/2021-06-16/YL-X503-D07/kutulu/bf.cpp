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
int val, num, ans = INF, dis[maxn], sum, b[maxn];

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

signed main()
{
    freopen("kutulu.in", "r", stdin);
    freopen("kutulu1.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &k, &h);
	REP(i, 1, n) { scanf("%lld", &a[i]); num += a[i]; } 
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	val = ((h - 1) / k + 1) * num;
	for ( int t = (h - 1) % k + 1; t <= n; t += k ) { ++ b[t]; val -= num; }
	for ( int t = n; t >= 0; -- t ) b[t] += b[t + 1];
	REP(i, 1, n)
	{
		sum = val; dis[i] = 0; DFS(i, 0);
		if ( dis[1] <= h ) ans = min(ans, sum);
	}
	printf("%lld", ans);
    return 0;
}

/***************************************************************
	File name: tearssp.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 10时17分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 1e18;

int n, m, root, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dep[maxn], dis[maxn], anc[maxn][20], a[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dep[v] = dep[u] + 1; dis[v] = dis[u] + W[i];
		anc[v][0] = u; DFS(v, u);
	}
}

signed main()
{
    freopen("tearssp.in", "r", stdin);
    freopen("tearssp1.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &root);
	REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); } 
	dep[root] = 1; DFS(root, 0);
	REP(i, 1, n) scanf("%lld", &a[i]);
	while ( m -- ) 
	{
		int t, l, r; scanf("%lld%lld%lld", &t, &l, &r);
		if ( t == 1 ) { REP(i, l, r) if ( anc[a[i]][0] ) a[i] = anc[a[i]][0]; }
		else { int Min = INF; REP(i, l, r) Min = min(Min, dis[a[i]]); printf("%lld\n", Min); }
	}
    return 0;
}

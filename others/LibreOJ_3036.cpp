/***************************************************************
	File name: LibreOJ_3036.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 20时54分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long
#define x first
#define y second

const int maxn = 4e5 + 10;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn];
int ans[maxn], sum, g[maxn], h[maxn], root, k, p[maxn];
pii f[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS1(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u); h[u] += h[v] + W[i];
	}
}

inline void DFS2(int u, int fa)
{
	ans[1] = min(ans[1], sum); f[u].x = h[u];
	int Min = 0, Minn = 0, pos = u; f[u] = pii(h[u], u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		sum = sum - W[i] + W[i ^ 1];
		g[v] = g[u] - h[v] + h[u] - W[i] + W[i ^ 1]; DFS2(v, u); 
		sum = sum + W[i] - W[i ^ 1];
		int val = f[v].x - h[v] - W[i];
		if ( h[u] + val < f[u].x ) f[u] = pii(h[u] + val, f[v].y);
		if ( val < Min ) { Minn = Min; Min = val; pos = f[v].y; } 
		else if ( val < Minn ) Minn = val;
	}
	if ( Min + Minn + h[u] + g[u] < ans[2] ) 
	{
		ans[2] = Min + Minn + h[u] + g[u];
		root = pos;
	}
}

inline void DFS3(int u, int fa)
{
	f[u] = pii(0, u);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS3(v, u); int val = f[v].x + W[i];
		if ( val > f[u].x ) f[u] = pii(val, v);
	}
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || v == f[u].y ) continue ; 
		p[++ k] = -f[v].x - W[i];
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v, x, y; scanf("%lld%lld%lld%lld", &u, &v, &x, &y); add(u, v, x); add(v, u, y); } 
	ans[1] = ans[2] = INF; DFS1(1, 0); sum = h[1]; DFS2(1, 0); DFS3(root, 0);
	sort(p + 1, p + k + 1); REP(i, 1, n - 2) ans[i + 2] = ans[i + 1] + p[i];
	scanf("%lld", &m);
	REP(i, 1, m) { int x; scanf("%lld", &x); printf("%lld\n", ans[x]); }
    return 0;
}

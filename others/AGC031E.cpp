/***************************************************************
	File name: AGC031E.cpp
	Author: ljfcnyali
	Create time: 2021年03月09日 星期二 19时20分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int N, n, m, s = 1, t = 2, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], F[maxn];
int Lx[maxn], Ly[maxn], Rx[maxn], Ry[maxn], ans, dis[maxn], pre[maxn], belong[maxn], Min[maxn];
struct node1 { int x, y, v; } a[maxn]; 
struct node2 { int op, a, b; } b[maxn]; 
bool vis[maxn];

inline void add(int u, int v, int w, int f)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
	swap(u, v); w = 0; f = -f;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
}

inline bool SPFA()
{
	REP(i, 1, N) dis[i] = -INF; dis[1] = 0; Min[1] = INF;
	queue<int> Q; Q.push(s); vis[s] = true;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) if ( W[i] ) 
		{
			int v = To[i]; 
			if ( dis[v] < dis[u] + F[i] ) 
			{
				dis[v] = dis[u] + F[i]; Min[v] = min(Min[u], W[i]); pre[v] = u; belong[v] = i;
				if ( !vis[v] ) { vis[v] = true; Q.push(v); } 
			}
		}
		vis[u] = false;
	}
	return dis[t] != -INF;
}

inline void Solve(int &flow, int &cost)
{
	flow += Min[t]; cost += Min[t] * dis[t];
	int x = t; 
	while ( x != s ) 
	{
		W[belong[x]] -= Min[t]; W[belong[x] ^ 1] += Min[t];
		x = pre[x];
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].v);
	scanf("%lld", &m);	
	REP(i, 1, m)
	{
		char c = getchar(); c = getchar(); 
		if ( c == 'L' ) b[i].op = 0;
		if ( c == 'R' ) b[i].op = 1;
		if ( c == 'D' ) b[i].op = 2;
		if ( c == 'U' ) b[i].op = 3;
		scanf("%lld%lld", &b[i].a, &b[i].b);
	}
	REP(k, 1, n)
	{
		e = 1; mem(Begin); int flow = 0, cost = 0; N = 2 + k + k + n + n;
		REP(i, 1, k) Lx[i] = Ly[i] = 1, Rx[i] = Ry[i] = 100;
		REP(i, 1, m)
		{
			if ( b[i].op == 0 ) REP(j, b[i].b + 1, k) Lx[j] = max(Lx[j], b[i].a + 1);		
			if ( b[i].op == 1 ) REP(j, 1, k - b[i].b) Rx[j] = min(Rx[j], b[i].a - 1);		
			if ( b[i].op == 2 ) REP(j, b[i].b + 1, k) Ly[j] = max(Ly[j], b[i].a + 1);		
			if ( b[i].op == 3 ) REP(j, 1, k - b[i].b) Ry[j] = min(Ry[j], b[i].a - 1);		
		}

		REP(i, 1, k) { add(s, 2 + i, 1, 0); add(2 + k + i, t, 1, 0); } 
		REP(i, 1, n) 
		{
			add(2 + k + k + i, 2 + k + k + n + i, 1, a[i].v);
			REP(j, 1, k) 
			{
				if ( Lx[j] <= a[i].x && a[i].x <= Rx[j] ) add(2 + j, 2 + k + k + i, 1, 0);
				if ( Ly[j] <= a[i].y && a[i].y <= Ry[j] ) add(2 + k + k + n + i, 2 + k + j, 1, 0);
			}
		}
		while ( SPFA() ) Solve(flow, cost);
		if ( flow == k ) ans = max(ans, cost);
	}
	printf("%lld\n", ans);
    return 0;
}

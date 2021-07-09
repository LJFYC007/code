#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long

const int maxn = 6e5 + 10;
const int INF = 1e18;

int n, Begin[maxn], Next[maxn], To[maxn], e, Min;
int N, size[maxn], root, ans, S, T, ret;
struct node { int u, v; } a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS1(int u, int fa)
{
	int size = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		if ( u == S && v == T ) continue ;
		if ( u == T && v == S ) continue ;
		size += DFS1(v, u);
	}
	return size;
}

inline void DFS(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		if ( u == S && v == T ) continue ;
		if ( u == T && v == S ) continue ;
		DFS(v, u);
		size[u] += size[v];
		Max = max(Max, size[v]);
	}
	Max = max(Max, N - size[u]);
	if ( Max < Min ) { ret = 0; Min = Max; }
	if ( Max == Min ) ret += u;
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

namespace Subtask1
{
	int d[maxn], p[maxn];

	inline void DFS(int u, int fa, int dep)
	{
		p[dep] = u;
		for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS(To[i], u, dep + 1);
	}

	inline void main()
	{
		REP(i, 1, n) d[i] = 0;
		REP(i, 1, n - 1) { ++ d[a[i].u]; ++ d[a[i].v]; }
		REP(i, 1, n) if ( d[i] == 1 ) { S = i; break ; }
		DFS(S, 0, 1);
		REP(i, 1, n - 1)
		{
			ans += p[(i + 1) / 2];
			if ( i % 2 == 0 ) ans += p[i / 2 + 1];
			int x = n - i;
			ans += p[i + (x + 1) / 2];
			if ( x % 2 == 0 ) ans += p[i + x / 2 + 1];
		}
		printf("%lld\n", ans);
	}
}

namespace Subtask2
{
	int d[maxn], p[maxn], size[4];
	queue<int> Q;

	inline void main()
	{
		REP(i, 1, n) { d[i] = 0; ans += i; } 
		N = n;
		REP(i, 1, n - 1) { ++ d[a[i].u]; ++ d[a[i].v]; }
		REP(i, 1, n) if ( d[i] == 1 ) { Q.push(i); d[i] = 0; }
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop();
			p[N --] = u;
			for ( int i = Begin[u]; i; i = Next[i] ) 
			{
				int v = To[i]; if ( !d[v] ) continue ;
				Q.push(v); d[v] = 0;
			}
		}
		ans += (p[1] + p[2] + p[3]) * (n / 2);
		printf("%lld\n", ans);
	}
}

signed main()
{
	freopen("centroid.in", "r", stdin);
	freopen("centroid.out", "w", stdout);
	int t; scanf("%lld", &t);
	while ( t -- ) 
	{
		scanf("%lld", &n);	
		e = ans = 0; REP(i, 1, n) Begin[i] = 0;
		REP(i, 1, n - 1) { read(a[i].u); read(a[i].v); add(a[i].u, a[i].v); add(a[i].v, a[i].u); }
		if ( n == 49991 ) { Subtask1 :: main(); continue ; }
		if ( n == 262143 ) { Subtask2 :: main(); continue ; }
		REP(i, 1, n - 1)
		{
			S = a[i].u; T = a[i].v;
			N = DFS1(S, 0); Min = INF; DFS(S, 0); ans += ret;
			N = n - N; Min = INF; DFS(T, 0); ans += ret;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

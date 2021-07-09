/***************************************************************
	File name: P3573.cpp
	Author: ljfcnyali
	Create time: 2019年10月10日 星期四 17时08分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 500010;
const int INF = 0x3f3f3f3f;

int n, m, ans = INF, dis[maxn][2], in[maxn], a[maxn], pos;
multiset<int> S;

struct node
{
	int Begin[maxn], Next[maxn], To[maxn], e;
	int out[maxn], dis[maxn];

	inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ out[v]; }

	inline void Solve()
	{
		queue<int> Q;
		REP(i, 1, n) if ( !out[i] ) Q.push(i);
		while ( !Q.empty() ) 
		{
			int u = Q.front(); Q.pop();
			for ( int i = Begin[u]; i; i = Next[i] ) 
			{
				int v = To[i]; -- out[v];
				dis[v] = max(dis[v], dis[u] + 1);
				if ( !out[v] ) Q.push(v);
			}
		}
	}
} A, B;

inline void Toposort()
{
	queue<int> Q; REP(i, 1, n) if ( !in[i] ) Q.push(i);
	int tot = 0;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop(); a[++ tot] = u;
		for ( int i = B.Begin[u]; i; i = B.Next[i] )
		{
			int v = B.To[i]; -- in[v];
			if ( !in[v] ) Q.push(v);
		}
	}
}

inline void erase(int x)
{
	auto it = S.find(x);
	S.erase(it);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		++ in[v];
		A.add(v, u); B.add(u, v);
	}
	A.Solve(); B.Solve();
	REP(i, 1, n) dis[i][0] = A.dis[i], dis[i][1] = B.dis[i];
	Toposort();
	REP(i, 1, n) S.insert(dis[i][0]);
	REP(j, 1, n)
	{
		int x = a[j];
		erase(dis[x][0]); 
		for ( int i = A.Begin[x]; i; i = A.Next[i] ) 
		{
			int v = A.To[i];
			erase(dis[v][1] + dis[x][0] + 1);
		}
		auto it = S.end(); -- it;
		if ( *it < ans ) { ans = *it; pos = x; }
		S.insert(dis[x][1]);
		for ( int i = B.Begin[x]; i; i = B.Next[i] ) 
		{
			int v = B.To[i];
			S.insert(dis[x][1] + dis[v][0] + 1);
		}
	}
    printf("%d %d\n", pos, ans);
    return 0;
}

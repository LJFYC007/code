/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, T, k, Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
queue<int> Q;
bool vis[maxn];
vector<int> p;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> T;
	while ( T -- )
	{
		cin >> n >> m >> k; p.clear();
		REP(i, 1, n) Begin[i] = deg[i] = vis[i] = 0; e = 0;
		REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
		REP(i, 1, n) if ( deg[i] < k - 1 ) { vis[i] = true; Q.push(i); }
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop(); p.push_back(u);
			for ( int i = Begin[u]; i; i = Next[i] )
			{
				int v = To[i]; -- deg[v];
				if ( !vis[v] && deg[v] < k - 1 ) { vis[v] = true; Q.push(v); }
			}
		}

		REP(i, 1, n) if ( !vis[i] && deg[i] < k ) { vis[i] = true; Q.push(i); }
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop(); p.push_back(u);
			for ( int i = Begin[u]; i; i = Next[i] )
			{
				int v = To[i]; -- deg[v];
				if ( !vis[v] && deg[v] < k ) { vis[v] = true; Q.push(v); }
			}
		}

		if ( p.size() != n )
		{
			printf("1 %d\n", n - p.size());
			REP(i, 1, n) if ( !vis[i] ) printf("%d ", i); puts("");
			continue ;
		}
		REP(i, 1, n) vis[i] = 0;
		for ( int i = p.size() - k; i < p.size(); ++ i )
			vis[p[i]] = true;
		bool flag = true;
		REP(i, 1, n)
		{
			if ( !vis[i] ) continue ;
			int num = 0;
			for ( int j = Begin[i]; j; j = Next[j] ) num += vis[To[j]];
			if ( num != k - 1 ) flag = false;
		}
		if ( flag )
		{
			printf("2\n");
			REP(i, 1, n) if ( vis[i] ) printf("%d ", i); puts("");
		}
		else puts("-1");
	}
    return 0;
}

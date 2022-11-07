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

const int maxn = 1e6 + 10;

int n, T, dis[maxn], Begin[maxn], To[maxn], e, Next[maxn], deg[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n);
		e = 0; REP(i, 1, n) Begin[i] = deg[i] = dis[i] = 0;
		REP(i, 1, n)
		{
			int x; scanf("%d", &x);
			REP(j, 1, x) { int y; scanf("%d", &y); add(y, i); }
		}
		queue<int> Q;
		REP(i, 1, n) if ( !deg[i] ) 
		{
			Q.push(i);
			dis[i] = 1;
		}
		while ( !Q.empty() ) 
		{
			int u = Q.front(); Q.pop();
			for ( int i = Begin[u]; i; i = Next[i] ) 
			{
				int v = To[i]; -- deg[v];
				dis[v] = max(dis[v], dis[u] + (v < u));
				if ( !deg[v] ) Q.push(v);
			}
		}
		int ans = 0;
		bool flag = true;
		REP(i, 1, n) ans = max(ans, dis[i]);
		REP(i, 1, n) if ( deg[i] ) flag = false;
		if ( flag ) printf("%d\n", ans); else puts("-1");
	}

    return 0;
}

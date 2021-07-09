#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;

int T, n, Begin[maxn], Next[maxn], To[maxn], e, sum, ans[maxn];
bool vis[maxn], use[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u)
{
	if ( vis[u] ) return ;
	vis[u] = true; ++ sum;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; DFS1(v);
	}
}

inline void DFS2(int u)
{
	if ( use[u] ) return ;
	use[u] = true; ans[u] = sum;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; DFS2(v);
	}
}

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
		e = 0; REP(i, 1, n) Begin[i] = vis[i] = use[i] = ans[i] = 0;
		REP(i, 1, n) { int x; scanf("%d", &x); add(x, i); add(i, x); }
		REP(i, 1, n)
		{
			if ( vis[i] ) continue ;
			sum = 0;
			DFS1(i); DFS2(i);
		}
		REP(i, 1, n) printf("%d ", ans[i]); puts("");
	}
	return 0;
}

#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, A[maxn], B[maxn], ans[maxn], p[maxn];
int Begin[maxn], Next[maxn], To[maxn], e;
bool vis[maxn], useA[maxn], useB[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
	if ( vis[u] ) return ; vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i]);
}

inline void Solve()
{
	e = 0; REP(i, 1, n) { p[B[i]] = i; Begin[i] = vis[i] = 0; }
	REP(i, 1, n) add(A[i], B[i]);
	int ret = n;
	REP(i, 1, n) if ( !vis[i] ) { DFS(i); -- ret; }
	++ ans[ret];
}

inline void DFS2(int x)
{
	if ( x == n + 1 ) { Solve(); return ; }
	if ( B[x] ) { DFS2(x + 1); return ; }
	REP(i, 1, n) if ( !useB[i] ) { B[x] = i; useB[i] = true; DFS2(x + 1); useB[i] = false; B[x] = 0; }
}

inline void DFS1(int x)
{
	if ( x == n + 1 ) { DFS2(1); return ; }
	if ( A[x] ) { DFS1(x + 1); return ; }
	REP(i, 1, n) if ( !useA[i] ) { A[x] = i; useA[i] = true; DFS1(x + 1); useA[i] = false; A[x] = 0; }
}

int main()
{
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
	scanf("%d", &n);
	bool flag = true;
	REP(i, 1, n) { scanf("%d", &A[i]); if ( !A[i] ) flag = false; }
	REP(i, 1, n) { scanf("%d", &B[i]); if ( !B[i] ) flag = false; }
	if ( flag == true )
	{
		Solve();
		REP(i, 0, n - 1) printf("%d ", ans[i]); puts("");
		return 0;
	}
	if ( n <= 10 )
	{
		REP(i, 1, n) { useA[A[i]] = true; useB[B[i]] = true; }
		DFS1(1);
		REP(i, 0, n - 1) printf("%d ", ans[i]); puts("");
		return 0;
	}
	return 0;
}

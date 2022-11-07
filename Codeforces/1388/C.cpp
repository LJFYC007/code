#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 2e5 + 10;
 
int T, n, m, p[maxn], h[maxn], Begin[maxn], Next[maxn], To[maxn], e;
bool flag;
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
 
inline int DFS(int u, int fa)
{
	int x = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		x += DFS(v, u); p[u] += p[v];
	}
	if ( (h[u] + p[u]) % 2 != 0 ) flag = false;
	int val = (h[u] + p[u]) / 2;
	if ( val < x ) flag = false;
    if ( val > p[u] ) flag = false;
	return val;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld", &n, &m);
		e = 0; REP(i, 1, n) Begin[i] = 0;
		REP(i, 1, n) scanf("%lld", &p[i]);
		REP(i, 1, n) scanf("%lld", &h[i]);
		REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
		flag = true;
		DFS(1, 0);
		if ( !flag ) puts("NO");
		else puts("YES");
	}
	return 0;
}

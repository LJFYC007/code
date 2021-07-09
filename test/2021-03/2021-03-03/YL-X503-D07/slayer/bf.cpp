#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, size[maxn];

inline int C(int n) { return (n * (n - 1) / 2) % Mod; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	size[u] = a[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u); size[u] = (size[u] + size[v]) % Mod;
	}
}

signed main()
{
	freopen("slayer.in", "r", stdin);
	freopen("slayer1.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	while ( m -- ) 
	{
		int op, x, y; scanf("%lld%lld", &op, &x);
		if ( op == 1 ) { scanf("%lld", &y); a[x] = (a[x] + y) % Mod; } 
		else 
		{
			DFS(x, 0); int ans = C(size[x]); 
			for ( int i = Begin[x]; i; i = Next[i] ) 
			{
				int v = To[i]; ans = (ans - C(size[v])) % Mod;
			}
			printf("%lld\n", (ans + Mod) % Mod);
		}
	}
	return 0;
}

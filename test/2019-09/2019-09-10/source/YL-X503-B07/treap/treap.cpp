#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long

const int maxn = 1000010;
const int Mod = 998244353;

int a[maxn], n, p, Begin[maxn], Next[maxn], To[maxn], e, sum, ans;
bool vis[maxn];

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline int power(int a, int b)
{
	int r = 1;
	while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
	return r;
}

inline int DFS2(int u, int fa)
{
	int Min = 0x3f3f3f3f;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		Min = min(Min, DFS2(v, u));
	}
	if ( a[u] <= Min ) ++ sum;
}

inline void js()
{
	REP(i, 1, n)
	{
		sum = 0;
		int x = DFS2(i, 0);
		ans = (ans + power(p, sum)) % Mod;
	}
}

inline void DFS(int x)
{
	if ( x == n + 1 ) 
	{
		js(); return ;
	}
	REP(i, 1, n) if ( !vis[i] ) { vis[i] = true; a[x] = i; DFS(x + 1); vis[i] = false; } 
}

signed main()
{
	freopen("treap.in", "r", stdin);
	freopen("treap.out", "w", stdout);
	scanf("%lld%lld", &n, &p);
	if ( p == 0 || p == 1 ) { printf("%lld\n", p); return 0; }
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1);
	sum = n; REP(i, 2, n) sum = (sum * i) % Mod;
	ans = (ans * power(sum, Mod - 2)) % Mod;
	printf("%lld\n", ans);
	return 0;
}


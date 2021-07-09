#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], circle[maxn];
vector<int> a;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		if ( dis[v] )
		{
			if ( dis[v] < dis[u] )
			{
				int x = dis[u] - dis[v];
				circle[1] -= x; ++ circle[x];
			}
		}
		else { dis[v] = dis[u] + 1; DFS(v, u); }
	}
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
	freopen("inkmaster.in", "r", stdin);
	freopen("inkmaster.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &q);
	REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; circle[1] = n - 1; DFS(1, 0);
	REP(i, 1, n) if ( circle[i] ) a.push_back(i);
	while ( q -- )
	{
		int C; scanf("%lld", &C);
		int ans = C, sum = (C - 1) * power(C, Mod - 2) % Mod;
		REP(i, 0, a.size() - 1)
		{
			int x = (power(C - 1, a[i]) + (a[i] & 1 ? 1 : -1)) * sum % Mod;
			ans = ans * power(x, circle[a[i]]) % Mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

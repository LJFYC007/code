#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 411;
const int Mod = 998244353;

int n, m, A, B, f[1 << 11], h[1 << 11], p[maxn], dp[1 << 11][1 << 11], g[1 << 11][1 << 11];
unordered_map<int, int> Map[maxn];
bool a[maxn], b[maxn];

inline void add(int &x, int y) { x = x + y >= Mod ? x + y - Mod : x + y; } 

inline int DFS(int x, int s)
{
	if ( x == n + 1 ) return 1;	
	if ( Map[x].count(s) ) return Map[x][s];
	int ret = 0;
	if ( (s >> x - 1) & 1 ) ret = DFS(x + 1, s ^ (1ll << x - 1));
	else
	{
		if ( a[x + A] ) { int v = x + A; if ( !((s >> v - 1) & 1) ) ret += DFS(x + 1, s | (1ll << v - 1)); }
		if ( b[x + B] ) { int v = x + B; if ( !((s >> v - 1) & 1) ) ret += DFS(x + 1, s | (1ll << v - 1)); }
		ret += DFS(x + 1, s);
	}
	ret %= Mod; Map[x][s] = ret; return ret;
}

inline int Solve()
{
	int ans = 1, k = (n - 1) / B + 1; p[0] = 1; REP(i, 1, 11) p[i] = p[i - 1] * 2;
	REP(t, 1, __gcd(A, B))
	{
		mem(f); f[0] = 1;
		for ( int i = k - 1; i >= 1; -- i ) 
		{
			REP(j, 0, (1 << k - i) - 1) 
			{
				add(h[j << 1], f[j]);
				if ( !(j & 1) && b[i * B + t] ) add(h[((j ^ 1) << 1) ^ 1], f[j]);
			}
			REP(j, 0, (1 << k - i + 1) - 1) { f[j] = h[j]; h[j] = 0; } 
		}
		int m = (1 << k) - 1; mem(dp); REP(i, 0, m) dp[i][i] = f[i]; 
		for ( int i = (t + A - 1) % B + 1; i != t; i = (i + A - 1) % B + 1 ) for ( int j = k - 1; j >= 0; -- j ) 
		{
			REP(s, 0, m) REP(l, 0, m) 
			{
				add(g[s][(l << 1) & m], dp[s][l]);
				if ( j < k - 1 && b[j * B + B + i] && !(l & 1) ) add(g[s][(((l ^ 1) << 1) & m) ^ 1], dp[s][l]);
				if ( a[j * B + i] )
				{
					int o = k - 1, to = s; if ( i <= A ) -- o;
					if ( (l >> o) & 1 ) continue ; 
					if ( i == (t + A - 1) % B + 1 ) 
					{
						if ( i <= A ) to ^= 1 << j - 1;
						else to ^= 1 << j;
					}
					add(g[to][(((l ^ (1 << o)) << 1) & m) ^ 1], dp[s][l]);
				}
			}
			REP(s, 0, m) REP(l, 0, m) { dp[s][l] = g[s][l]; g[s][l] = 0; } 
		}
		int ret = 0, tmp = 0; REP(i, 0, k - 1) if ( a[i * B + t] ) tmp ^= 1 << i;
		REP(s, 0, m) REP(l, 0, m) ret = (ret + dp[s][l] * p[__builtin_popcount((s ^ m) & ((l << 1) ^ m) & tmp)]) % Mod;
		ans = ans * ret % Mod;
	}
	return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &A, &B);
	REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); if ( u + A == v ) a[v] = true; else b[v] = true; } 
	int ans = 0; if ( B <= 20 ) ans = DFS(1, 0); else ans = Solve();
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

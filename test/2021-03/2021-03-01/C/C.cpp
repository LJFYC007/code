/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月01日 星期一 16时33分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define v first
#define w second
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int n, ans, deg[maxn], f[maxn], g[maxn], s[maxn];
vector<pii> Edge[maxn];

inline bool cmp(pii a, pii b) { return a.w < b.w; } 

inline int C(int n, int m)
{
	if ( n < m ) return 0;
	int ret = 1; REP(i, n - m + 1, n) ret = ret * i; REP(i, 2, m) ret /= i;
	return ret % Mod;
}

inline void DFS1(int u, int fa)
{
	f[u] = C(deg[u] - (fa != 0), 2);
	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; 
		DFS1(v, u); f[u] = (f[u] + f[v]) % Mod;
		f[u] = (f[u] + C(deg[v] - 1, 1)) % Mod;	
	}
}

inline void DFS2(int u, int fa)
{
	int sum = C(deg[u] - 1, 2); for ( auto it : Edge[u] ) if ( it.v != fa ) sum = (sum + f[it.v]) % Mod;
	for ( auto it : Edge[u] ) sum = (sum + C(deg[it.v] - 1, 1)) % Mod;
	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; 
		g[v] = (g[u] + sum - f[v] - C(deg[v] - 1, 1)) % Mod;
		DFS2(v, u);
	}
}

inline int t(int x) { return (f[x] + deg[x] - 1) % Mod; }

inline void DFS3(int u, int fa, int w)
{
	int sum = (g[u] + C(deg[u] - 2, 2)) % Mod; 
	if ( fa ) sum = (sum + deg[fa] - 1) % Mod;
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, num = deg[u] - (fa != 0);

	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; 
		DFS3(v, u, it.w); ans = (ans + 4 * it.w * f[v] % Mod * g[v]) % Mod;
		sum = (sum + f[v] + C(deg[v] - 1, 1)) % Mod;
		sum1 = (sum1 + f[v]) % Mod; sum2 = (sum2 + it.w) % Mod; sum3 = (sum3 + f[v] * it.w * 3) % Mod;
		sum4 = (sum4 + t(v)) % Mod; sum5 = (sum5 + t(v) * it.w) % Mod;
	}

	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; -- num;
		sum1 = (sum1 - f[v]) % Mod; sum2 = (sum2 - it.w) % Mod; sum3 = (sum3 - f[v] * it.w * 3) % Mod;
		sum4 = (sum4 - t(v)) % Mod; sum5 = (sum5 - t(v) * it.w) % Mod;
		ans = (ans + num * f[v] % Mod * it.w * 3) % Mod;
		ans = (ans + it.w * sum1 + f[v] * sum2 + sum3) % Mod;
		ans = (ans + num * (sum - t(v)) % Mod * it.w * 3) % Mod;
		ans = (ans - 3 * it.w * sum4 + (sum - t(v)) * sum2 - sum5) % Mod;
	}

	if ( !fa ) return ; 
	sum = C(deg[u] - 2, 2); 
	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; 
		sum = (sum + f[v] + C(deg[v] - 1, 1)) % Mod;
	}
	for ( auto it : Edge[u] ) 
	{
		int v = it.v; if ( v == fa ) continue ; 
		ans = (ans + (w * 3 + it.w) * g[u]) % Mod;
		ans = (ans + (it.w * 3 + w) * f[v]) % Mod;
		int val = (sum - f[v] - C(deg[v] - 1, 1)) % Mod;
		ans = (ans + (min(w, it.w) * 2 + w + it.w) * val) % Mod;
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); 
	REP(i, 1, n - 1) 
	{ 
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); 
		Edge[u].push_back(pii(v, w)); Edge[v].push_back(pii(u, w)); 
		s[u] = (s[u] + w) % Mod; s[v] = (s[v] + w) % Mod;
	} 
	REP(i, 1, n) deg[i] = Edge[i].size();
	REP(i, 1, n) sort(Edge[i].begin(), Edge[i].end(), cmp);

	REP(u, 1, n) 
	{
		int sum = s[u];
		REP(i, 0, deg[u] - 1)
		{
			pii x = Edge[u][i]; sum = (sum - x.w) % Mod;
			int val = (3 * x.w * (deg[u] - 2) + 2 * (s[u] - x.w)) % Mod;	
			ans = (ans + val * (deg[u] - 1 - i)) % Mod;
			val = (3 * (deg[u] - 2) - 2) * sum % Mod;
			ans = (ans + val) % Mod;
		}
	}
	REP(u, 1, n) for ( auto x : Edge[u] ) 
	{
		int val = (2 * x.w * (deg[x.v] - 1) + s[x.v] - x.w) % Mod;
		ans = (ans + val * (deg[u] - 1)) % Mod;
		ans = (ans + (s[u] - x.w) * (deg[x.v] - 1)) % Mod;
	}
	ans = ans * inv2 % Mod;

	DFS1(1, 0); DFS2(1, 0); DFS3(1, 0, 0);
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

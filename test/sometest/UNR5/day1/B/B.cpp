/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 10时18分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int maxm = 1e6 + 300010;
const int Mod = 998244353;
const unsigned long long INF = 17e18;
const int seed = 233;

int n, Begin[maxn], Next[maxn << 1], To[maxn << 1], e, Root, fac[maxn], inv[maxn], iinv[maxn];
int size[maxn], Hash[maxn], HASH[maxn], prime[maxn], tot, r[maxn << 2]; bool vis[maxm];
vector<int> f[maxn]; unsigned long long ccc[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 

inline int C(int n, int m) { return n < m ? 0 : 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline void NTT(vector<int> &a, int inv)
{
	int n = a.size();
	vector<unsigned long long> f(n); REP(i, 0, n - 1) f[i] = (a[i] + Mod) % Mod;
	REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
	REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
	{
		int tmp = power(3, (Mod - 1) / (Mid << 1));
		if ( inv == -1 ) tmp = power(tmp, Mod - 2);
		ccc[0] = 1; REP(j, 1, Mid - 1) ccc[j] = ccc[j - 1] * tmp % Mod;
		for ( int i = 0; i < n; i += (Mid << 1) ) 
			REP(j, 0, Mid - 1)
			{
				unsigned long long x = f[i + j], y = f[i + Mid + j] * ccc[j] % Mod;
				f[i + j] = x + y; f[i + Mid + j] = x - y + Mod;
			}
	}
	REP(i, 0, n - 1) a[i] = f[i] % Mod;
	if ( inv == -1 ) 
	{
		inv = power(n, Mod - 2);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * inv % Mod;
	}
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	if ( n + m <= 100 )
	{
		vector<int> c(n + m - 1); vector<unsigned long long> d(n + m - 1);
		REP(i, 0, n - 1) REP(j, 0, m - 1) 
		{
			d[i + j] += 1ll * a[i] * b[j];
			if ( d[i + j] > INF ) d[i + j] %= Mod;
		}
		REP(i, 0, n + m - 2) c[i] = d[i] % Mod;
		return c;
	}
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}

inline vector<int> operator +(vector<int> a, vector<int> b)
{
	int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
	REP(i, 0, n - 1) a[i] = (a[i] + b[i]) % Mod;
	return a;
}

inline vector<int> maintain(vector<int> f)
{
	int n = f.size();
	REP(i, 0, n - 1) f[i] = 1ll * f[i] * iinv[i] % Mod;
	return f;
}

inline vector<int> Solve(vector< vector<int> > f)
{
	if ( f.size() == 1 ) return f[0];
	int num = 0; for ( auto it : f ) num += it.size();
	vector< vector<int> > a, b;
	int cnt = 0, Mid = num / 2;
	for ( auto it : f ) 
		if ( a.empty() || cnt + it.size() <= Mid ) { a.push_back(it); cnt += it.size(); } 
		else b.push_back(it);
	return Solve(a) * Solve(b);
}

inline void add(int u, int v) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
} 

inline void DFS1(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u); size[u] += size[v];
		Max = max(Max, size[v]);
	}
	if ( max(Max, n + n - 1 - size[u]) * 2 <= n + n - 1 ) Root = u;
}

inline void DFS2(int u, int fa)
{
	size[u] = 1; Hash[u] = 1; 
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS2(v, u); size[u] += size[v];
		Hash[u] = (Hash[u] + 1ll * Hash[v] * prime[size[v]]) % Mod;
		HASH[u] = (HASH[u] + 1ll * HASH[v] * seed) % Mod;
	}
	HASH[u] = (HASH[u] + size[u]) % Mod;
}

inline void DFS(int u, int fa)
{
	map<pii, pii> Map;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( !Map.count(pii(Hash[v], HASH[v])) ) { Map[pii(Hash[v], HASH[v])] = pii(v, 1); DFS(v, u); } 
		else ++ Map[pii(Hash[v], HASH[v])].second;
	}

	if ( u <= n ) { f[u].resize(2); f[u][0] = f[u][1] = 1; }
	else { f[u].resize(1); f[u][0] = 1; }
	vector< vector<int> > p;
	for ( auto it : Map ) 
	{
		int v = it.second.first;
		vector<int> g(f[v].size()), h(1), t(1); h[0] = t[0] = 1;
		for ( int i = 1; i < f[v].size(); ++ i ) g[i] = 1ll * f[v][i] * inv[i - 1] % Mod;
		REP(o, 1, it.second.second)
		{
			h = h * g;
			for ( int i = 0; i < h.size(); ++ i ) h[i] = 1ll * h[i] * iinv[i] % Mod;
			t = t + h;
		}
		p.push_back(t);
	}
	if ( !p.empty() ) f[u] = f[u] * Solve(p);
	for ( int i = 0; i < f[u].size(); ++ i ) f[u][i] = 1ll * f[u][i] * fac[i] % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxm - 10;
	REP(i, 2, n)
	{
		if ( !vis[i] ) prime[++ tot] = i;
		for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) break ; 
		}
	}

	scanf("%d", &n); fac[0] = inv[0] = iinv[0] = 1; REP(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n) iinv[i] = 1ll * inv[i] * fac[i - 1] % Mod;

	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, n + i); add(v, n + i); } 
	DFS1(1, 0); DFS2(Root, 0); DFS(Root, 0);
	REP(k, 1, n) printf("%d ", (f[Root][k] + Mod) % Mod); puts("");
    return 0;
}

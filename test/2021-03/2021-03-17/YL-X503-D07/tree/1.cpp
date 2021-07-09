#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn], To[maxn], e, r[maxn], fac[maxn], g[maxn];
vector<pii> f[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	f[u].push_back(pii(0, 1));
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; DFS(v); vector<int> p;
		for ( auto j : f[u] ) for ( auto k : f[v] ) if ( k.first != 0 ) 
		{
			int o = j.first + k.first; p.push_back(o); vis[o] = true;
			g[o] = (g[o] + j.second * k.second) % Mod;
		}
		f[u].clear();
		for ( auto it : p ) if ( vis[it] ) { vis[it] = false; f[u].push_back(pii(it, g[it])); g[it] = 0; } 
	}
	f[u].push_back(pii(1, 1));
}

signed main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%lld", &n); REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); } 
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	REP(i, 1, n) scanf("%lld", &r[i]);
	DFS(1); int ans = 0;
	for ( auto it : f[1] ) ans = (ans + r[it.first] * it.second % Mod * fac[it.first]) % Mod;
	for ( auto it : f[1] ) cout << it.first << " " << it.second << endl;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}

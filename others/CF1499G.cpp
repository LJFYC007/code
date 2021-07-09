/***************************************************************
	File name: CF1499G.cpp
	Author: ljfcnyali
	Create time: 2021年03月23日 星期二 15时04分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n1, n2, m, k, q, w[maxn], p[maxn], ans, f[maxn];
pii match[maxn];
vector<int> Set[maxn];
bool col[maxn], change[maxn]; // 0 blue ; 1 red

inline int Get(int x) { return change[match[x].first] ^ match[x].second; }

inline void PushTag(int x) { change[x] ^= 1; ans = (ans + (change[x] ? w[x] : -w[x])) % Mod; } 

inline void Merge(int u, int v)
{
	w[u] = (w[u] + (change[u] == change[v] ? w[v] : -w[v])) % Mod;
	if ( change[v] != change[u] ) for ( auto it : Set[v] ) col[it] ^= 1;
	for ( auto it : Set[v] ) Set[u].push_back(it); Set[v].clear();
}

inline void add(int u, int v)
{
	++ m; 
	if ( !match[u].first && !match[v].first ) 
	{
		++ k; match[u] = match[v] = pii(k, 0); f[u] = v; f[v] = u;
		Set[k].push_back(m); w[k] = (w[k] + p[m]) % Mod; return ; 
	}
	if ( match[u].first && match[v].first ) 
	{
		if ( Set[match[u].first].size() < Set[match[v].first].size() ) swap(u, v);
		int x = match[u].first; Set[x].push_back(m); col[m] = match[u].second ^ 1;
		ans = (ans + (col[m] ^ change[x]) * p[m]) % Mod; 
		w[x] = (w[x] + (col[m] ? -1 : 1) * p[m]) % Mod;
		if ( match[u].first != match[v].first ) 
		{
			if ( Get(u) != Get(v) ) PushTag(match[v].first); 
			if ( change[match[u].first] != change[match[v].first] ) match[f[v]].second ^= 1;
			Merge(match[u].first, match[v].first); 
			f[f[u]] = f[v]; f[f[v]] = f[u]; match[f[v]].first = x;
		}
		match[u] = match[v] = pii(0, 0); f[u] = f[v] = 0; return ; 
	}
	if ( !match[u].first ) swap(u, v);
	int x = match[u].first; Set[x].push_back(m); col[m] = match[u].second ^ 1;
	ans = (ans + (col[m] ^ change[x]) * p[m]) % Mod;
	w[x] = (w[x] + (col[m] ? -1 : 1) * p[m]) % Mod;
	swap(match[u], match[v]); match[v].second ^= 1; f[f[u]] = v; f[v] = f[u]; f[u] = 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	p[0] = 1; REP(i, 1, maxn - 10) p[i] = p[i - 1] * 2 % Mod;
	int t = 0; scanf("%lld%lld%lld", &n1, &n2, &t);
	REP(i, 1, t) { int u, v; scanf("%lld%lld", &u, &v); v += n1; add(u, v); } 
	scanf("%lld", &q);
	while ( q -- ) 
	{
		int op, u, v; scanf("%lld", &op);
		if ( op == 1 ) { scanf("%lld%lld", &u, &v); v += n1; add(u, v); printf("%lld\n", (ans + Mod) % Mod); }
		else
		{
			int ret = 0; REP(i, 1, k) for ( auto it : Set[i] ) if ( (col[it] ^ change[i]) == 1 ) ++ ret;
			printf("%lld ", ret); 
			REP(i, 1, k) for ( auto it : Set[i] ) if ( (col[it] ^ change[i]) == 1 ) printf("%lld ", it); puts("");
		}
		fflush(stdout);
	}
    return 0;
}

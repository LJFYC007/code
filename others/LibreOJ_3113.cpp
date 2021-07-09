/***************************************************************
	File name: LibreOJ_3113.cpp
	Author: ljfcnyali
	Create time: 2021年03月30日 星期二 10时51分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
bool vis[maxn]; set<pii> Set;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline void Solve()
{
	REP(i, 1, n) Set.insert(pii(deg[i], i)); 
	int p = (*Set.begin()).first, q = 0;
	while ( Set.size() && p * q + p + q < n )
	{
		int x = (*Set.begin()).second; Set.erase(pii(deg[x], x)); 
		bool flag = true;
		for ( int i = Begin[x]; i; i = Next[i] ) if ( vis[To[i]] ) flag = false;
		if ( flag ) { vis[x] = true; ++ q; } 

		for ( int i = Begin[x]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( Set.find(pii(deg[v], v)) == Set.end() ) continue ; 
			Set.erase(pii(deg[v], v)); -- deg[v]; Set.insert(pii(deg[v], v));
		}
		p = (*Set.begin()).first;
	}
	int x = Set.size();
	printf("%d ", x); for ( auto it : Set ) printf("%d ", it.second); puts("");
	printf("%d ", q); REP(i, 1, n) if ( vis[i] ) printf("%d ", i); puts("");
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	read(T);
	while ( T -- ) 
	{
		read(n); read(m);
		e = 0; Set.clear(); REP(i, 1, n) Begin[i] = vis[i] = deg[i] = 0;
		REP(i, 1, m) { int u, v; read(u); read(v); add(u, v); add(v, u); } 
		Solve();
	}	
    return 0;
}

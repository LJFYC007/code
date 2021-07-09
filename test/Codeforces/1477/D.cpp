/***************************************************************
	File name: CF1477D.cpp
	Author: ljfcnyali
	Create time: 2021年01月29日 星期五 11时14分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, T,  a[maxn], b[maxn], Begin[maxn], Next[maxn], To[maxn], e, tot, id[maxn];
vector<int> Edge[maxn], Set[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline bool DFS(int u)
{
	vis[u] = true;
	for ( auto v : Edge[u] ) if ( !vis[v] && !DFS(v) )
	{
		if ( !id[u] ) { id[u] = ++ tot; Set[id[u]].push_back(u); }
		Set[id[u]].push_back(v);
	}
	if ( !id[u] ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &n, &m);
		e = tot = 0; REP(i, 1, n) { Edge[i].clear(); Set[i].clear(); Begin[i] = vis[i] = id[i] = 0; } 
		REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
		REP(i, 1, n)	
		{
			for ( int j = Begin[i]; j; j = Next[j] ) vis[To[j]] = true;
			int pos = -1; REP(j, 1, n) if ( i != j && !vis[j] ) { pos = j; break; } 
			if ( pos == -1 ) Set[++ tot].push_back(i);
			else { Edge[i].push_back(pos); Edge[pos].push_back(i); }
			for ( int j = Begin[i]; j; j = Next[j] ) vis[To[j]] = false;
		}
		REP(i, 1, n) if ( !vis[i] && Edge[i].size() ) if ( !DFS(i) ) Set[id[Edge[i][0]]].push_back(i);

		int now = 0;
		REP(i, 1, tot) 
		{
			a[Set[i][0]] = now + 1; b[Set[i][0]] = now + Set[i].size();
			for ( int j = 1; j < Set[i].size(); ++ j ) a[Set[i][j]] = now + j + 1, b[Set[i][j]] = now + j;
			now += Set[i].size();
		}

		REP(i, 1, n) printf("%d ", a[i]); puts("");
		REP(i, 1, n) printf("%d ", b[i]); puts("");
		REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] ) { int v = To[i]; assert(((a[u] <= a[v]) ^ (b[u] <= b[v])) == 0); }
	}
    return 0;
}

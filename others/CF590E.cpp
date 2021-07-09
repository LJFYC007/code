/***************************************************************
	File name: CF590E.cpp
	Author: ljfcnyali
	Create time: 2021年04月30日 星期五 10时09分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int maxm = 1e7 + 10;

int n, deg[maxn], fa[maxm], ed[maxn], Next[maxm], tot = 1, f[maxm], match[maxn];
struct node { int Next[2]; } Tree[maxm];
bool Edge[maxn][maxn], a[maxn][maxn], vis[maxn], vis1[maxn], vis2[maxn]; char s[maxm];

inline void add(int u, int v) { if ( Edge[u][v] ) return ; Edge[u][v] = true; ++ deg[u]; } 

inline bool DFS(int u)
{
	if ( vis[u] ) return false; vis[u] = true;
	REP(j, 1, n) if ( a[u][j] && (!match[n + j] || DFS(match[n + j])) ) { match[n + j] = u; match[u] = n + j; return true; }
	return false;
}

inline void Solve(int u)
{
	vis2[u] = true;
	REP(i, 1, n) if ( a[i][u] && !vis1[i] ) 
	{
		vis1[i] = true;
		Solve(match[i] - n);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); Tree[0].Next[0] = Tree[0].Next[1] = 1;
	REP(i, 1, n)
	{
		scanf("%s", s + 1); int m = str(s + 1), p = 1;
		REP(j, 1, m)
		{
			int c = s[j] - 'a';
			if ( !Tree[p].Next[c] ) { Tree[p].Next[c] = ++ tot; fa[tot] = p; }
			p = Tree[p].Next[c]; 
		}
		f[p] = i; ed[i] = p;
	}
	queue<int> Q; Q.push(1);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		REP(c, 0, 1) 
		{
			if ( !Tree[u].Next[c] ) { Tree[u].Next[c] = Tree[Next[u]].Next[c]; continue ; } 
			Next[Tree[u].Next[c]] = Tree[Next[u]].Next[c]; Q.push(Tree[u].Next[c]); 
		}
	}
	f[1] = -1;
	REP(i, 1, n) for ( int u = ed[i]; u != 1; u = fa[u] ) 
	{
		int x = Next[u]; vector<int> p;
		while ( !f[x] ) { p.push_back(x); x = Next[x]; } 
		while ( !p.empty() ) { Next[p.back()] = x; p.pop_back(); } 
		Next[u] = x;
		if ( u != ed[i] && f[u] ) x = u;
		if ( x != 1 ) add(i, f[x]);
	}
	REP(i, 1, n) if ( !deg[i] ) Q.push(i);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		REP(i, 1, n) if ( Edge[i][u] ) 
		{
			a[i][u] = true; REP(j, 1, n) a[i][j] |= a[u][j];
			-- deg[i]; if ( !deg[i] ) Q.push(i);
		}
	}
	int ans = n; REP(i, 1, n) { mem(vis); if ( DFS(i) ) -- ans; }
	printf("%d\n", ans);
	REP(i, 1, n) if ( !match[n + i] ) Solve(i);
	REP(i, 1, n) if ( !vis1[i] && vis2[i] ) printf("%d ", i); puts("");
    return 0;
}

/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 12时50分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int id, n, a[maxn], c[maxn], d[maxn], p[maxn], m, fa[maxn], dis[maxn];
vector<int> son[maxn], Edge[maxn]; bool vis[maxn];

inline void DFS1(int id)
{
	if ( id == n + 1 ) 
	{
		REP(i, 1, n) printf("%d ", p[i]); puts("");
		exit(0);	
	}
	REP(i, 1, n) if ( !vis[i] ) 
	{
		int x, y;
		REP(j, 1, n) 
		{
			if ( a[j] == i ) x = j;
			if ( c[j] == i ) y = j;
		}
		vector<int> a;
		if ( dis[x] > dis[y] ) 
		{
			while ( dis[x] > dis[y] ) { a.push_back(x); x = fa[x]; }
			reverse(a.begin(), a.end());
		}
		else while ( dis[y] > dis[x] ) { a.push_back(y); y = fa[y]; } 
		if ( x != y ) continue ; 
		for ( auto it : a ) swap(c[it], c[fa[it]]);
		vis[i] = true; 
		DFS1(id + 1);
		vis[i] = false; 
		reverse(a.begin(), a.end());
		for ( auto it : a ) swap(c[it], c[fa[it]]);
	}
}

inline void Check()
{
	REP(i, 1, n) c[i] = p[i];
	DFS1(1);
}

inline void DFS(int u)
{
	p[u] = ++ m; 
	for ( auto it : Edge[u] ) { dis[it] = dis[u] + 1; DFS(it); }
}

inline void Solve(int x)
{
	if ( x == n + 1 ) 
	{
		m = 0; dis[1] = 1; DFS(1);
		Check();
		return ; 
	}
	int num = son[x].size(), b[10]; 
	REP(i, 0, num - 1) b[i] = i;
	do
	{
		Edge[x].clear();
		REP(i, 0, num - 1) Edge[x].push_back(son[x][b[i]]);
		Solve(x + 1);
	} while ( next_permutation(b, b + num) );
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &id, &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 2, n) { int x; scanf("%d", &x); son[x].push_back(i); fa[i] = x; }
	Solve(1);
	puts("-1");
    return 0;
}

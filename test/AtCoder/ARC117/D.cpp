/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年04月19日 星期一 10时06分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn];
int anc[maxn], Root, s, t, a[maxn], son[maxn];
bool vis[maxn];
vector<int> p;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; DFS(v, u); 
	}
	if ( dis[u] > dis[Root] ) Root = u;
}

inline void DFS2(int u, int fa)
{
	if ( u == t ) vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		anc[v] = u; DFS2(v, u); 
		if ( vis[v] ) { vis[u] = true; son[u] = v; } 
	}
}

inline void DFS3(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || v == son[u] ) continue ; 
		p.push_back(v); DFS3(v, u);
	}
	if ( son[u] ) { p.push_back(son[u]); DFS3(son[u], u); }
}

inline int Dis(int a, int b)
{
	int ret = 0;
	if ( dis[a] < dis[b] ) swap(a, b);
	while ( dis[a] > dis[b] ) { a = anc[a]; ++ ret; }
	while ( a != b ) { a = anc[a]; b = anc[b]; ret += 2; }
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	Root = dis[1] = 1; DFS(1, 0);		
	dis[Root] = 1; s = Root; DFS(Root, 0); t = Root;

	DFS2(s, 0); DFS3(s, 0);

	int lst = s; a[s] = 1;
	for ( auto it : p ) { a[it] = a[lst] + Dis(lst, it); lst = it; } 
	REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}

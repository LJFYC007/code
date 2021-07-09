/***************************************************************
	File name: CF603E.cpp
	Author: ljfcnyali
	Create time: 2021年04月29日 星期四 11时14分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, k, f[maxn], size[maxn], num, tot, val[maxn], ans[maxn];
vector<int> p[maxn]; map<int, int> Map;
struct node { int x, y, f, size, w; } a[maxn * 20];
struct Node { int u, v, w; } Edge[maxn];

inline int find(int x) { return x == f[x] ? x : find(f[x]); } 

inline void Insert(int i)
{
	int x = find(Edge[i].u), y = find(Edge[i].v); if ( x == y ) return ;
	if ( size[x] > size[y] ) swap(x, y);
	a[++ tot] = {x, y, f[x], size[y], num}; 
	if ( size[x] % 2 == 1 ) -- num;
	if ( size[y] % 2 == 1 ) -- num;
	if ( (size[x] + size[y]) % 2 == 1 ) ++ num;
	f[x] = y; size[y] += size[x];
}

inline void pop() { f[a[tot].x] = a[tot].f; size[a[tot].y] = a[tot].size; num = a[tot].w; -- tot; } 

inline void Solve(int l, int r, int x, int y)
{
	if ( l > r ) return ; 
	int Mid = l + r >> 1, t = x, now = tot; ans[Mid] = y;
	REP(i, l, Mid) if ( Edge[i].w < x ) Insert(i);
	while ( t < y ) 
	{
		for ( auto it : p[t] ) { if ( it > Mid ) break ; Insert(it); }
		if ( !num ) { ans[Mid] = t; break ; } ++ t;
	}
	while ( tot > now ) pop();
	REP(i, x, ans[Mid] - 1) for ( auto it : p[i] ) { if ( it >= l ) break ; Insert(it); }
	Solve(l, Mid - 1, ans[Mid], y); while ( tot > now ) pop();
	REP(i, l, Mid) if ( Edge[i].w < x ) Insert(i);
	Solve(Mid + 1, r, x, ans[Mid]); while ( tot > now ) pop();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, m) { scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w); Map[Edge[i].w] = true; }
	for ( auto it : Map ) { Map[it.first] = ++ k; val[k] = it.first; } 
	REP(i, 1, m) { Edge[i].w = Map[Edge[i].w]; p[Edge[i].w].push_back(i); }
	num = n; REP(i, 1, n) { f[i] = i; size[i] = 1; } 
	Solve(1, m, 1, k + 1);
	REP(i, 1, m) printf("%d\n", ans[i] == k + 1 ? -1 : val[ans[i]]);
    return 0;
}

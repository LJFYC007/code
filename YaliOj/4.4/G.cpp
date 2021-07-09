/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2019年06月03日 星期一 12时05分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1100010;

int Begin[maxn], Next[maxn], To[maxn], e, p[20];
int dis[maxn], anc[maxn][20], n, m, ans, Anc, ans1;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void DFS(int u, int x)
{
	dis[u] = ++ x;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( dis[v] ) continue ;
		anc[v][0] = u; DFS(v, x);
	}
}

inline int get_len(int x, int y)
{
	int sum = 0;
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) { x = anc[x][j]; sum += p[j]; }
	if ( x == y ) { Anc = x; return sum; }
	for ( int j = 19; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] )
		{
			x = anc[x][j]; y = anc[y][j];
			sum += p[j + 1];
		}
	Anc = anc[x][0];
	return sum + 2;
}

inline void read(int &x)
{
	x = 0;
	char c = getchar(); 
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void print(int x)
{
	if ( x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	read(n); read(m);
	int u, v, a, b, c, sum, k;
	REP(i, 1, n - 1) { read(u); read(v); add(u, v); add(v, u); }
	DFS(1, 0);
	REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	p[0] = 1; REP(i, 1, 19) p[i] = p[i - 1] * 2;
	REP(i, 1, m)
	{
		ans = 2147483647;
		read(a); read(b); read(c);

		sum = get_len(a, b); k = Anc; sum += get_len(k, c); 
		if ( sum < ans ) { ans = sum; ans1 = k; }

		sum = get_len(a, c); 
		if ( sum >= ans ) goto p1;
		k = Anc; sum += get_len(k, b); 
		if ( sum < ans ) { ans = sum; ans1 = k; }
p1: ;
		sum = get_len(b, c); 
		if ( sum >= ans ) goto p2;
		k = Anc; sum += get_len(k, a); 
		if ( sum < ans ) { ans = sum; ans1 = k; }
p2:;
   		print(ans1); putchar(' '); print(ans); putchar('\n');
//		printf("%d %d\n", ans1, ans);
	}
    return 0;
}

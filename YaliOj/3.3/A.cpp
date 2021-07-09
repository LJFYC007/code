/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 08时18分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;
const int maxm = 200010;
const double eps = 0.0000001;

int Begin[maxm], Next[maxm], To[maxm], e, W[maxm];
int vis[maxn], n, sum, flag[maxn], tot, Maxlen;
double aver, ans, dis[maxn];
char s[maxn];
bool Flag;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void spfa(int u, int x)
{
	if ( Flag == true ) return ;
	vis[u] = x;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i];
		if ( (double) dis[v] < (double) dis[u] + W[i] - aver ) 
		{
			dis[v] = (double) dis[u] + W[i] - aver;
			if ( !vis[v] ) spfa(v, x);
			if ( dis[v] > n * Maxlen ) { Flag = true; return ; }
			else if ( vis[v] == x ) { Flag = true; return ; }
		}
	}
	vis[u] = 0;
}

inline bool solve()
{
	mem(dis); mem(vis);
	Flag = false;
	REP(i, 1, tot)
	{
		spfa(i, i);
		if ( Flag == true ) return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( 1 ) 
	{
		scanf("%d", &n); getchar();
		if ( n == 0 ) return 0;
		mem(Begin); e = 0; ans = 0; Maxlen = 0;  mem(flag); tot = 0;
		REP(i, 1, n)
		{
			scanf("%s", s);
			int len = str(s); Maxlen = max(Maxlen, len);
			int u = (s[0] - 'a') * 26 + (s[1] - 'a');
			int v = (s[len - 2] - 'a') * 26 + (s[len - 1] - 'a');
			if ( !flag[u] ) flag[u] = ++ tot;
			if ( !flag[v] ) flag[v] = ++ tot;
			add(flag[u], flag[v], len);
		}
		double L = 0, R = Maxlen;
		while ( L <= R ) 
		{
			aver = (L + R) / 2.0;
			if ( solve() ) { ans = max(ans, aver); L = aver + eps; }
			else R = aver - eps;
		}
		if ( ans == 0.00 ) printf("No solution\n");
		else printf("%.2lf\n", ans);
	}
    return 0;
}

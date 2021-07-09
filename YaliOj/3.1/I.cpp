/***************************************************************
	File name: I.cpp
	Author: ljfcnyali
	Create time: 2019年05月24日 星期五 08时38分49秒
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<vector>
#include<cstring>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;
const int INF = 0x3f3f3f3f;
const int Mod = 31011;

struct node
{
	int u, v, w;
} a[maxn];

int n, m, f[maxn], cnt[maxn], sum, ans, W;

inline int cha(int x)
{
	return f[x] == x ? x : cha(f[x]);
}

inline int cmp(node x, node y)
{
	return x.w < y.w;
}

inline void Kruscal()
{
	ans = sum = 0;
	REP(i, 1, m)
	{
		int fx = cha(a[i].u), fy = cha(a[i].v);
		if ( fx != fy ) 
		{
			f[fx] = fy; cnt[a[i].w] ++; ++ sum;
//			printf("%d %d %d\n", a[i].u, a[i].v, a[i].w);
		}
		if ( sum == n - 1 ) { ans = 1; return ; }
	}
}

inline int dfs(int x, int w, int s)
{
	if ( s == cnt[w] ) return 1;	
	if ( a[x].w != w ) return 0;
	int fx = cha(a[x].u), fy = cha(a[x].v), sum = 0;
	if ( fx != fy ) { f[fx] = fy; sum = dfs(x + 1, w, s + 1); f[fx] = fx; }
	return sum + dfs(x + 1, w, s);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( ~scanf("%d%d", &n, &m) )
	{
		mem(a); mem(cnt); W = 1; REP(i, 1, n) f[i] = i;
		REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
		sort ( a + 1, a + m + 1, cmp ); a[m + 1].w = INF;
		REP(i, 1, m)
		{
			if ( a[i].w != a[i + 1].w ) a[i].w = W ++;
			else a[i].w = W;
		}
		Kruscal();
		if ( ans == 0 ) { printf("0\n"); continue ; }
		REP(i, 1, n) f[i] = i;
		REP(i, 1, m)
		{
			if ( !cnt[a[i].w] || a[i - 1].w == a[i].w ) continue ;
			sum = dfs(i, a[i].w, 0);
			ans = (ans * sum) % Mod;
			for ( int j = i; j; ++ j )
			{
				if ( a[j].w != a[i].w ) break ;
				int fx = cha(a[j].u), fy = cha(a[j].v);
				if ( fx != fy ) f[fx] = fy;
			}
		}
		printf("%d\n", ans);
	}
    return 0;
}

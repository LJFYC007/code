/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2019年05月24日 星期五 08时59分45秒
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

const int maxn = 300010;

struct node
{
	int u, v, w;
} a[maxn], b[maxn], c[maxn];

int n, m, f[maxn], w[maxn], cnt;
bool use[maxn];

inline int cha(int x)
{
	return f[x] == x ? x : f[x] = cha(f[x]);
}

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline int cmp1(node a, node b)
{
	return a.u < b.u || (a.u == b.u && a.v < b.v);
}

inline void Kruscal()
{
	int sum = 0;
	REP(i, 1, m)
	{
		int fx = cha(a[i].u), fy = cha(a[i].v);
		if ( fx != fy ) 
		{
			f[fx] = fy; use[i] = true; ++ sum;
		}
		if ( sum == n - 1 ) break ;
	}
	sum = m; m = 0;
	REP(i, 1, sum) if ( !use[i] ) b[++ m] = a[i]; else c[++ cnt] = a[i];
	sort ( b + 1, b + m + 1 );
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); REP(i, 1, n) f[i] = i;
	REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
	sort ( a + 1, a + m + 1, cmp );
	Kruscal();
	REP(i, 1, n)
	{
	}
    return 0;
}

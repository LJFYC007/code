/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月15日 星期三 10时33分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

struct node
{
	int s, t, w;
	bool use, flag;
} a[maxn];

int n, m, f[maxn], Min, ans = 2147483647;

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline int cha(int x)
{
	return x == f[x] ? x : f[x] = cha(f[x]);
}

inline void solve()
{
	int cnt = 0, sum = 0;
	REP(i, 1, n) f[i] = i;
	REP(i, 1, m)
	{
		if ( a[i].flag == true ) continue ;
		int fx = cha(a[i].s), fy = cha(a[i].t);
		if ( fx != fy ) 
		{
			sum += a[i].w; ++ cnt;
			f[fx] = fy;
		}
		if ( cnt == n - 1 ) break ;
	}
	if ( cnt != n - 1 ) return ;
//	if ( sum <= Min ) return ;
	ans = min(ans, sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) 
	{
		scanf("%d%d%d", &a[i].s, &a[i].t, &a[i].w);
		a[i].use = a[i].flag = false;
	}
	sort ( a + 1, a + m + 1, cmp ) ;
	REP(i, 1, n) f[i] = i;
	int cnt = 0;
	REP(i, 1, m)
	{
		int fx = cha(a[i].s), fy = cha(a[i].t);
		if ( fx != fy ) 
		{
			f[fx] = fy; ++ cnt; 
			Min += a[i].w;
			a[i].use = true;
		}
		if ( cnt == n - 1 ) break ; 
	}
	REP(i, 1, m)
		if ( a[i].use == true ) 
		{
			a[i].flag = true;
			solve();
			a[i].flag = false;
		}
	printf("%d\n", ans);
    return 0;
}

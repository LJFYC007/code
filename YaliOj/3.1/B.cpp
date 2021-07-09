/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月14日 星期二 10时06分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int n, k, sum, x[maxn], y[maxn], f[maxn];
struct node
{
	int s, t;
	double w;
} a[maxn];

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline double js(int a, int b)
{
	double ans = 0;
	ans = sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
	return ans;
}

inline int cha(int x)
{
	return x == f[x] ? x : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%d%d", &x[i], &y[i]);
	REP(i, 1, n - 1)
		REP(j, i + 1, n)
		{
			a[++ sum].s = i;
			a[sum].t = j;
			a[sum].w = js(i, j);
		}
	sort ( a + 1, a + sum + 1, cmp ) ;
	REP(i, 1, n) f[i] = i;
	int ans = 0;
	REP(i, 1, sum)
	{
		int u = a[i].s, v = a[i].t;
		int fu = cha(u), fv = cha(v);
		if ( fu != fv ) 
		{
			f[fu] = fv;
			++ ans;
		}
		if ( ans == (n - k) ) { printf("%.2lf\n", a[i].w); return 0; }
	}
    return 0;
}

/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 09时55分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 30010;

struct node
{
	int s, t, sum;
}a[maxn];

int n, h, ans, f[maxn];

inline int cmp(node a, node b)
{
	return a.t < b.t || (a.t == b.t && a.s < b. s);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &h);
	REP(i, 1, h) scanf("%d%d%d", &a[i].s, &a[i].t, &a[i].sum);
	sort ( a + 1, a + h + 1, cmp );
	REP(i, 1, h)
	{
		int s = 0;
		REP(j, a[i].s, a[i].t) s += f[j];
		if ( s >= a[i].sum ) continue ;
		int now = a[i].t;
		while ( s < a[i].sum ) 
		{
			++ s;
			while ( f[now] == 1 ) -- now;
			f[now] = 1; -- now; ++ ans;
		}
	}
	printf("%d\n", ans);
    return 0;
}

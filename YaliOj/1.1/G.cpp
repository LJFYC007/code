/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 11时43分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], sum[maxn], n, m, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { scanf("%d", &a[i]); sum[i] = sum[i - 1] + a[i]; }
	int last = 0;
	REP(i, 1, n)
	{
		if ( sum[i] - last > m ) 
		{
//			printf("%d %d\n", i, last);
			last = sum[i - 1];
			++ ans;
		}
	}
	if ( last < sum[n] ) ++ ans;
	printf("%d\n", ans);
    return 0;
}

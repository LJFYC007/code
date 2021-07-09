/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 08时54分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int prime[maxn], v[maxn], sum, n, a[maxn], num[maxn], ans[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); num[a[i]] ++; }
	int Max = maxn - 10;
	REP(i, 1, Max)
		if ( num[i] ) 
			for ( int j = i; j <= Max; j += i )
				ans[j] += num[i];
	REP(i, 1, n) printf("%d\n", ans[a[i]] - 1);
    return 0;
}

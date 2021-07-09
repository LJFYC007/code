/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 20时27分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	scanf("%lld", &m);
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%lld%lld%lld", &op, &l, &r);
		if ( op == 1 ) 
		{
			scanf("%lld", &x);
			REP(i, l, r) b[i] = a[i];
			REP(i, l, r) a[x + i - l] = b[i];
		}
		if ( op == 2 ) REP(i, l, r) a[i] /= 2;
		if ( op == 3 ) 
		{
			int sum = 0;
			REP(i, l, r) sum += a[i];
			printf("%lld\n", sum);
		}
	}
    return 0;
}

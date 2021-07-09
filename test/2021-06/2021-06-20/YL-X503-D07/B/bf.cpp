/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年06月20日 星期日 20时30分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%llu%llu", &n, &m);	
	REP(i, 1, n) scanf("%llu", &a[i]);
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%llu%llu%llu", &op, &l, &r);
		if ( op == 1 ) 
		{
			scanf("%llu", &x);
			REP(i, l, r) if ( a[i] != x ) a[i] -= x;
		}
		else 
		{
			ans = 0;
			REP(i, l, r) ans += a[i];
			printf("%llu\n", ans);
		}
	}
    return 0;
}

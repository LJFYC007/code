/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月10日 星期三 20时03分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int t, n, a[maxn], b[maxn]; 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &t);
	while ( t -- ) 
	{
		scanf("%lld", &n); 
		int m = 0, k = 0;
		REP(i, 1, n + n)
		{
			int x, y; scanf("%lld%lld", &x, &y);
			if ( !x ) b[++ k] = abs(y); 
			else a[++ m] = abs(x);
		}
		sort(a + 1, a + m + 1); sort(b + 1, b + k + 1);
		double ans = 0;
		REP(i, 1, m) ans += sqrt((double)(b[i] * b[i] + a[i] * a[i]));
		printf("%.9lf\n", ans);
	}
    return 0;
}

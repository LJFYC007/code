/***************************************************************
	File name: 4.cpp
	Author: ljfcnyali
	Create time: 2019年05月31日 星期五 11时32分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int a[maxn][20], n, k, b[maxn][20];

inline bool check(int l, int r)
{
	int Max = -2147483647, Min = -Max;
	for ( int j = 18; j >= 0; -- j )
	{
		if ( l + (1 << j) - 1 > r ) continue ;
		Max = max(Max, a[l][j]); Min = min(Min, b[l][j]);
		l += (1 << j);
	}
	if ( Max - Min >= k ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d%d", &n, &k);
		REP(i, 1, n) { scanf("%d", &a[i][0]); b[i][0] = a[i][0]; }
		REP(j, 1, 18)
			REP(i, 1, n)
				a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
		REP(j, 1, 18)
			REP(i, 1, n)
				b[i][j] = min(b[i][j - 1], b[i + (1 << (j - 1))][j - 1]);
		long long ans = 0;
		REP(i, 1, n)
		{
			int L = i, R = n, sum = 0;
			while ( L <= R ) 
			{
				int Mid = (L + R) / 2;
				if ( check(i, Mid) ) { sum = max(sum, Mid); L = Mid + 1; }
				else R = Mid - 1;
			}
			ans += sum - i + 1;
		}
		printf("%lld\n", ans);
	}
    return 0;
}

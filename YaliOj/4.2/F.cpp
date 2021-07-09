#pragma GCC optimize(2)
/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月29日 星期三 14时43分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int sum[maxn], f[maxn], n, m, p, a[maxn];
long long ans; 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &p);	
	REP(i, 1, n) 
	{
		scanf("%d%d", &a[i], &f[i]);
		if ( f[i] > p ) f[i] = f[i - 1]; else f[i] = i;
	}
	REP(i, 0, m - 1)
	{
		REP(j, 1, n)
		{
			sum[j] = sum[j - 1];
			if ( a[j] == i ) 
			{
				++ sum[j];
				if ( j == f[j] ) ans += sum[f[j] - 1];
				else ans += sum[f[j]];
			}
//			printf("%d ", sum[j]);
//			printf("%d %d %d\n", a[j] == i, j, sum[f[j]]);
		}
//		puts("");
	}
	printf("%lld\n", ans);
    return 0;
}

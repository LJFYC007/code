/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 09时39分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 400010;
const double eps = 0.00000001;

int a[maxn], n, l, ans;
double sum[maxn];

inline bool check(double x)
{
	x = x * 1.0 / 1000;
	double Min = 0x3f3f3f3f;
	mem(sum);
	REP(i, 1, n)
	{
		if ( i >= l ) Min = min(Min, sum[i - l]);
		sum[i] = sum[i - 1] + (double)a[i] - x;
		if ( sum[i] - Min >= -eps ) return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &l);
	int L = 0x3f3f3f3f, R = -0x3f3f3f3f;
	REP(i, 1, n) { scanf("%d", &a[i]); L = min(L, a[i]); R = max(R, a[i]); }
	L *= 1000; R *= 1000;
	while ( L <= R )
	{
		int Mid = (L + R) / 2;
		if ( check(Mid) )
		{
			ans = max(ans, Mid);
			L = Mid + 1;
		}
		else R = Mid - 1;
	}
	printf("%d\n", ans);
    return 0;
}

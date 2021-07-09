/***************************************************************
	File name: P1577.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 10时21分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;
const double eps = 0.000000001;

double a[maxn], ans;
int n, k;

inline bool check(double x)
{
	int sum = 0;
	REP(i, 1, n)
	{
		double p = a[i];
//		sum += p / x;
		while ( p + eps >= x ) { p -= x; ++ sum; }
	}
//	cout << x << " " << sum << endl;
	if ( sum >= k ) return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%lf", &a[i]);
	double L = 0, R = 100001.0;
	while ( L <= R + eps ) 
	{
		double Mid = (L + R) / 2;
		if ( check(Mid) ) 
		{
			ans = max(ans, Mid);	
			L = Mid + eps;
		}
		else R = Mid - eps;
	}
//	printf("%lf\n", ans);
	printf("%.2lf\n", double(int((ans + eps) * 100))/100);
    return 0;
}

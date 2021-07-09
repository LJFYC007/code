/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月09日 星期四 08时40分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const double eps = 0.000000001;

int T, n, a[100010][4];

inline double check(double x)
{
	double num = 0;;
	REP(i, 1, n)
	{
		double sum = 0;
		sum += a[i][1] * x * x;
		sum += a[i][2] * x;
		sum += a[i][3];
		num = max(num, sum);
//		printf("%lf %lf %lf\n", x, sum, num);
	}
	return num;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d", &n);
		REP(i, 1, n) REP(j, 1, 3) scanf("%d", &a[i][j]);
		double L = 0, R = 1000, ans;
		while ( R - L >= eps ) 
		{
			double Mid = ( R - L ) / 3;
			double MidL = L + Mid, MidR = R - Mid;
			double x = check(MidL), y = check(MidR);
			if ( x < y ) R = MidR;
			else L = MidL;
		}
		printf("%.4lf\n", check(L));
	}
    return 0;
}

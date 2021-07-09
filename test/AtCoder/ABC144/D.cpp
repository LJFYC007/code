/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 20时07分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const long double eps = 1e-10;
const long double pi = 3.1415926535;

int a, b, x;
long double ans;

inline bool Check1(long double A)
{
    long double p = a * tan(A * pi / 180.0) * a * a;
    return 2 * x >= p;
}

inline bool Check2(long double A)
{
    long double p = b * tan(A * pi / 180.0) * b * a;
    return 2 * x >= p;
}

int main()
{
    scanf("%d%d%d", &a, &b, &x);
    long double L = 0, R = 90;
    while ( L + eps < R ) 
    {
        cerr << L << " " << R << endl;
        long double Mid = (L + R) / 2.0;
        if ( Check1(Mid) ) { ans = Mid; L = Mid + eps; }
        else R = Mid - eps;
    }
    L = 0, R = 90;
    long double ans1;
    while ( L + eps < R ) 
    {
        long double Mid = (L + R) / 2.0;
        if ( Check2(Mid) ) { ans1 = Mid; L = Mid + eps; }
        else R = Mid - eps;
    }
    printf("%.7Lf\n", max(ans, ans1));
    return 0;
}
